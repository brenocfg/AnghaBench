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
typedef  int u64 ;
struct cxl_afu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AFUD_CR_LEN (int) ; 
 int AFUD_EB_LEN (int) ; 
 int AFUD_NUM_CRS (int) ; 
 int AFUD_NUM_INTS_PER_PROC (int) ; 
 int AFUD_NUM_PROCS (int) ; 
 int AFUD_PPPSA_LEN (int) ; 
 int AFUD_READ (struct cxl_afu*,int) ; 
 int AFUD_READ_CR (struct cxl_afu*) ; 
 int AFUD_READ_CR_OFF (struct cxl_afu*) ; 
 int AFUD_READ_EB (struct cxl_afu*) ; 
 int AFUD_READ_EB_OFF (struct cxl_afu*) ; 
 int AFUD_READ_INFO (struct cxl_afu*) ; 
 int AFUD_READ_LE (struct cxl_afu*,int) ; 
 int AFUD_READ_PPPSA (struct cxl_afu*) ; 
 int AFUD_READ_PPPSA_OFF (struct cxl_afu*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*,int) ; 

__attribute__((used)) static void dump_afu_descriptor(struct cxl_afu *afu)
{
	u64 val, afu_cr_num, afu_cr_off, afu_cr_len;
	int i;

#define show_reg(name, what) \
	dev_info(&afu->dev, "afu desc: %30s: %#llx\n", name, what)

	val = AFUD_READ_INFO(afu);
	show_reg("num_ints_per_process", AFUD_NUM_INTS_PER_PROC(val));
	show_reg("num_of_processes", AFUD_NUM_PROCS(val));
	show_reg("num_of_afu_CRs", AFUD_NUM_CRS(val));
	show_reg("req_prog_mode", val & 0xffffULL);
	afu_cr_num = AFUD_NUM_CRS(val);

	val = AFUD_READ(afu, 0x8);
	show_reg("Reserved", val);
	val = AFUD_READ(afu, 0x10);
	show_reg("Reserved", val);
	val = AFUD_READ(afu, 0x18);
	show_reg("Reserved", val);

	val = AFUD_READ_CR(afu);
	show_reg("Reserved", (val >> (63-7)) & 0xff);
	show_reg("AFU_CR_len", AFUD_CR_LEN(val));
	afu_cr_len = AFUD_CR_LEN(val) * 256;

	val = AFUD_READ_CR_OFF(afu);
	afu_cr_off = val;
	show_reg("AFU_CR_offset", val);

	val = AFUD_READ_PPPSA(afu);
	show_reg("PerProcessPSA_control", (val >> (63-7)) & 0xff);
	show_reg("PerProcessPSA Length", AFUD_PPPSA_LEN(val));

	val = AFUD_READ_PPPSA_OFF(afu);
	show_reg("PerProcessPSA_offset", val);

	val = AFUD_READ_EB(afu);
	show_reg("Reserved", (val >> (63-7)) & 0xff);
	show_reg("AFU_EB_len", AFUD_EB_LEN(val));

	val = AFUD_READ_EB_OFF(afu);
	show_reg("AFU_EB_offset", val);

	for (i = 0; i < afu_cr_num; i++) {
		val = AFUD_READ_LE(afu, afu_cr_off + i * afu_cr_len);
		show_reg("CR Vendor", val & 0xffff);
		show_reg("CR Device", (val >> 16) & 0xffff);
	}
#undef show_reg
}