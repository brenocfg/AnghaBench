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
struct TYPE_2__ {unsigned int sig; } ;
struct ucode_cpu_info {TYPE_1__ cpu_sig; } ;
struct cpio_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_X86_32 ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ __pa_nodebug (void*) ; 
 struct cpio_data find_microcode_in_initrd (char const*,int) ; 
 int /*<<< orphan*/  get_builtin_microcode (struct cpio_data*,int /*<<< orphan*/ ) ; 
 void* ucode_cpu_info ; 
 void* ucode_path ; 
 int /*<<< orphan*/  x86_family (unsigned int) ; 

__attribute__((used)) static void __load_ucode_amd(unsigned int cpuid_1_eax, struct cpio_data *ret)
{
	struct ucode_cpu_info *uci;
	struct cpio_data cp;
	const char *path;
	bool use_pa;

	if (IS_ENABLED(CONFIG_X86_32)) {
		uci	= (struct ucode_cpu_info *)__pa_nodebug(ucode_cpu_info);
		path	= (const char *)__pa_nodebug(ucode_path);
		use_pa	= true;
	} else {
		uci     = ucode_cpu_info;
		path	= ucode_path;
		use_pa	= false;
	}

	if (!get_builtin_microcode(&cp, x86_family(cpuid_1_eax)))
		cp = find_microcode_in_initrd(path, use_pa);

	/* Needed in load_microcode_amd() */
	uci->cpu_sig.sig = cpuid_1_eax;

	*ret = cp;
}