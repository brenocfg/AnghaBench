#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t u8 ;
struct cper_sec_proc_ia {int validation_bits; struct cper_ia_proc_ctx* cpuid; int /*<<< orphan*/  lapic_id; } ;
struct cper_ia_proc_ctx {int reg_arr_size; size_t reg_ctx_type; int /*<<< orphan*/  mm_reg_addr; int /*<<< orphan*/  msr_addr; } ;
struct cper_ia_err_info {int validation_bits; int /*<<< orphan*/  ip; int /*<<< orphan*/  responder_id; int /*<<< orphan*/  requestor_id; int /*<<< orphan*/  target_id; int /*<<< orphan*/  check_info; int /*<<< orphan*/  err_type; } ;
typedef  int /*<<< orphan*/  newpfx ;
typedef  int /*<<< orphan*/  infopfx ;

/* Variables and functions */
 size_t ARRAY_SIZE (char**) ; 
 size_t CTX_TYPE_MMREG ; 
 size_t CTX_TYPE_MSR ; 
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int INFO_VALID_CHECK_INFO ; 
 int INFO_VALID_IP ; 
 int INFO_VALID_REQUESTOR_ID ; 
 int INFO_VALID_RESPONDER_ID ; 
 int INFO_VALID_TARGET_ID ; 
 size_t N_ERR_TYPES ; 
 int VALID_CPUID_INFO ; 
 int VALID_LAPIC_ID ; 
 int VALID_PROC_CXT_INFO_NUM (int) ; 
 int VALID_PROC_ERR_INFO_NUM (int) ; 
 size_t cper_get_err_type (int /*<<< orphan*/ *) ; 
 char** cper_proc_error_type_strs ; 
 char** ia_reg_ctx_strs ; 
 int /*<<< orphan*/  print_err_info (char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_hex_dump (char const*,char*,int /*<<< orphan*/ ,int,int,struct cper_ia_proc_ctx*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,char const*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

void cper_print_proc_ia(const char *pfx, const struct cper_sec_proc_ia *proc)
{
	int i;
	struct cper_ia_err_info *err_info;
	struct cper_ia_proc_ctx *ctx_info;
	char newpfx[64], infopfx[64];
	u8 err_type;

	if (proc->validation_bits & VALID_LAPIC_ID)
		printk("%sLocal APIC_ID: 0x%llx\n", pfx, proc->lapic_id);

	if (proc->validation_bits & VALID_CPUID_INFO) {
		printk("%sCPUID Info:\n", pfx);
		print_hex_dump(pfx, "", DUMP_PREFIX_OFFSET, 16, 4, proc->cpuid,
			       sizeof(proc->cpuid), 0);
	}

	snprintf(newpfx, sizeof(newpfx), "%s ", pfx);

	err_info = (struct cper_ia_err_info *)(proc + 1);
	for (i = 0; i < VALID_PROC_ERR_INFO_NUM(proc->validation_bits); i++) {
		printk("%sError Information Structure %d:\n", pfx, i);

		err_type = cper_get_err_type(&err_info->err_type);
		printk("%sError Structure Type: %s\n", newpfx,
		       err_type < ARRAY_SIZE(cper_proc_error_type_strs) ?
		       cper_proc_error_type_strs[err_type] : "unknown");

		if (err_type >= N_ERR_TYPES) {
			printk("%sError Structure Type: %pUl\n", newpfx,
			       &err_info->err_type);
		}

		if (err_info->validation_bits & INFO_VALID_CHECK_INFO) {
			printk("%sCheck Information: 0x%016llx\n", newpfx,
			       err_info->check_info);

			if (err_type < N_ERR_TYPES) {
				snprintf(infopfx, sizeof(infopfx), "%s ",
					 newpfx);

				print_err_info(infopfx, err_type,
					       err_info->check_info);
			}
		}

		if (err_info->validation_bits & INFO_VALID_TARGET_ID) {
			printk("%sTarget Identifier: 0x%016llx\n",
			       newpfx, err_info->target_id);
		}

		if (err_info->validation_bits & INFO_VALID_REQUESTOR_ID) {
			printk("%sRequestor Identifier: 0x%016llx\n",
			       newpfx, err_info->requestor_id);
		}

		if (err_info->validation_bits & INFO_VALID_RESPONDER_ID) {
			printk("%sResponder Identifier: 0x%016llx\n",
			       newpfx, err_info->responder_id);
		}

		if (err_info->validation_bits & INFO_VALID_IP) {
			printk("%sInstruction Pointer: 0x%016llx\n",
			       newpfx, err_info->ip);
		}

		err_info++;
	}

	ctx_info = (struct cper_ia_proc_ctx *)err_info;
	for (i = 0; i < VALID_PROC_CXT_INFO_NUM(proc->validation_bits); i++) {
		int size = sizeof(*ctx_info) + ctx_info->reg_arr_size;
		int groupsize = 4;

		printk("%sContext Information Structure %d:\n", pfx, i);

		printk("%sRegister Context Type: %s\n", newpfx,
		       ctx_info->reg_ctx_type < ARRAY_SIZE(ia_reg_ctx_strs) ?
		       ia_reg_ctx_strs[ctx_info->reg_ctx_type] : "unknown");

		printk("%sRegister Array Size: 0x%04x\n", newpfx,
		       ctx_info->reg_arr_size);

		if (ctx_info->reg_ctx_type == CTX_TYPE_MSR) {
			groupsize = 8; /* MSRs are 8 bytes wide. */
			printk("%sMSR Address: 0x%08x\n", newpfx,
			       ctx_info->msr_addr);
		}

		if (ctx_info->reg_ctx_type == CTX_TYPE_MMREG) {
			printk("%sMM Register Address: 0x%016llx\n", newpfx,
			       ctx_info->mm_reg_addr);
		}

		printk("%sRegister Array:\n", newpfx);
		print_hex_dump(newpfx, "", DUMP_PREFIX_OFFSET, 16, groupsize,
			       (ctx_info + 1), ctx_info->reg_arr_size, 0);

		ctx_info = (struct cper_ia_proc_ctx *)((long)ctx_info + size);
	}
}