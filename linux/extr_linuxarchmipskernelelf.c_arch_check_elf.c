#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mode_req {int single; int soft; int fr1; int frdefault; int fre; } ;
struct elf64_hdr {int e_flags; } ;
struct elf32_hdr {scalar_t__* e_ident; int e_flags; } ;
struct arch_elf_state {int nan_2008; int fp_abi; int interp_fp_abi; void* overall_fp_mode; } ;
struct TYPE_2__ {int fpu_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_MIPS_O32_FP64_SUPPORT ; 
 int EF_MIPS_ABI2 ; 
 int EF_MIPS_NAN2008 ; 
 size_t EI_CLASS ; 
 scalar_t__ ELFCLASS32 ; 
 int ELIBBAD ; 
 int ENOEXEC ; 
 void* FP_FR0 ; 
 void* FP_FR1 ; 
 void* FP_FRE ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int MIPS_ABI_FP_64A ; 
 int MIPS_ABI_FP_SOFT ; 
 int MIPS_ABI_FP_UNKNOWN ; 
 int MIPS_FPIR_F64 ; 
 scalar_t__ cpu_has_mips_r2_r6 ; 
 scalar_t__ cpu_has_mips_r6 ; 
 struct mode_req* fpu_reqs ; 
 int max (int,int) ; 
 int min (int,int) ; 
 scalar_t__ mips_use_nan_2008 ; 
 scalar_t__ mips_use_nan_legacy ; 
 struct mode_req none_req ; 
 TYPE_1__ raw_current_cpu_data ; 

int arch_check_elf(void *_ehdr, bool has_interpreter, void *_interp_ehdr,
		   struct arch_elf_state *state)
{
	union {
		struct elf32_hdr e32;
		struct elf64_hdr e64;
	} *ehdr = _ehdr;
	union {
		struct elf32_hdr e32;
		struct elf64_hdr e64;
	} *iehdr = _interp_ehdr;
	struct mode_req prog_req, interp_req;
	int fp_abi, interp_fp_abi, abi0, abi1, max_abi;
	bool elf32;
	u32 flags;

	elf32 = ehdr->e32.e_ident[EI_CLASS] == ELFCLASS32;
	flags = elf32 ? ehdr->e32.e_flags : ehdr->e64.e_flags;

	/*
	 * Determine the NaN personality, reject the binary if not allowed.
	 * Also ensure that any interpreter matches the executable.
	 */
	if (flags & EF_MIPS_NAN2008) {
		if (mips_use_nan_2008)
			state->nan_2008 = 1;
		else
			return -ENOEXEC;
	} else {
		if (mips_use_nan_legacy)
			state->nan_2008 = 0;
		else
			return -ENOEXEC;
	}
	if (has_interpreter) {
		bool ielf32;
		u32 iflags;

		ielf32 = iehdr->e32.e_ident[EI_CLASS] == ELFCLASS32;
		iflags = ielf32 ? iehdr->e32.e_flags : iehdr->e64.e_flags;

		if ((flags ^ iflags) & EF_MIPS_NAN2008)
			return -ELIBBAD;
	}

	if (!IS_ENABLED(CONFIG_MIPS_O32_FP64_SUPPORT))
		return 0;

	fp_abi = state->fp_abi;

	if (has_interpreter) {
		interp_fp_abi = state->interp_fp_abi;

		abi0 = min(fp_abi, interp_fp_abi);
		abi1 = max(fp_abi, interp_fp_abi);
	} else {
		abi0 = abi1 = fp_abi;
	}

	if (elf32 && !(flags & EF_MIPS_ABI2)) {
		/* Default to a mode capable of running code expecting FR=0 */
		state->overall_fp_mode = cpu_has_mips_r6 ? FP_FRE : FP_FR0;

		/* Allow all ABIs we know about */
		max_abi = MIPS_ABI_FP_64A;
	} else {
		/* MIPS64 code always uses FR=1, thus the default is easy */
		state->overall_fp_mode = FP_FR1;

		/* Disallow access to the various FPXX & FP64 ABIs */
		max_abi = MIPS_ABI_FP_SOFT;
	}

	if ((abi0 > max_abi && abi0 != MIPS_ABI_FP_UNKNOWN) ||
	    (abi1 > max_abi && abi1 != MIPS_ABI_FP_UNKNOWN))
		return -ELIBBAD;

	/* It's time to determine the FPU mode requirements */
	prog_req = (abi0 == MIPS_ABI_FP_UNKNOWN) ? none_req : fpu_reqs[abi0];
	interp_req = (abi1 == MIPS_ABI_FP_UNKNOWN) ? none_req : fpu_reqs[abi1];

	/*
	 * Check whether the program's and interp's ABIs have a matching FPU
	 * mode requirement.
	 */
	prog_req.single = interp_req.single && prog_req.single;
	prog_req.soft = interp_req.soft && prog_req.soft;
	prog_req.fr1 = interp_req.fr1 && prog_req.fr1;
	prog_req.frdefault = interp_req.frdefault && prog_req.frdefault;
	prog_req.fre = interp_req.fre && prog_req.fre;

	/*
	 * Determine the desired FPU mode
	 *
	 * Decision making:
	 *
	 * - We want FR_FRE if FRE=1 and both FR=1 and FR=0 are false. This
	 *   means that we have a combination of program and interpreter
	 *   that inherently require the hybrid FP mode.
	 * - If FR1 and FRDEFAULT is true, that means we hit the any-abi or
	 *   fpxx case. This is because, in any-ABI (or no-ABI) we have no FPU
	 *   instructions so we don't care about the mode. We will simply use
	 *   the one preferred by the hardware. In fpxx case, that ABI can
	 *   handle both FR=1 and FR=0, so, again, we simply choose the one
	 *   preferred by the hardware. Next, if we only use single-precision
	 *   FPU instructions, and the default ABI FPU mode is not good
	 *   (ie single + any ABI combination), we set again the FPU mode to the
	 *   one is preferred by the hardware. Next, if we know that the code
	 *   will only use single-precision instructions, shown by single being
	 *   true but frdefault being false, then we again set the FPU mode to
	 *   the one that is preferred by the hardware.
	 * - We want FP_FR1 if that's the only matching mode and the default one
	 *   is not good.
	 * - Return with -ELIBADD if we can't find a matching FPU mode.
	 */
	if (prog_req.fre && !prog_req.frdefault && !prog_req.fr1)
		state->overall_fp_mode = FP_FRE;
	else if ((prog_req.fr1 && prog_req.frdefault) ||
		 (prog_req.single && !prog_req.frdefault))
		/* Make sure 64-bit MIPS III/IV/64R1 will not pick FR1 */
		state->overall_fp_mode = ((raw_current_cpu_data.fpu_id & MIPS_FPIR_F64) &&
					  cpu_has_mips_r2_r6) ?
					  FP_FR1 : FP_FR0;
	else if (prog_req.fr1)
		state->overall_fp_mode = FP_FR1;
	else  if (!prog_req.fre && !prog_req.frdefault &&
		  !prog_req.fr1 && !prog_req.single && !prog_req.soft)
		return -ELIBBAD;

	return 0;
}