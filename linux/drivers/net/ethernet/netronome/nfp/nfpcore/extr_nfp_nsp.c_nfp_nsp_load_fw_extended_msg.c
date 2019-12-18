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
typedef  int /*<<< orphan*/  u32 ;
struct nfp_nsp {int /*<<< orphan*/  cpp; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char const* const*) ; 
 unsigned int FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* KERN_DEBUG ; 
 char* KERN_ERR ; 
 char* KERN_INFO ; 
 int /*<<< orphan*/  NFP_FW_LOAD_RET_MAJOR ; 
 int /*<<< orphan*/  NFP_FW_LOAD_RET_MINOR ; 
 int /*<<< orphan*/  nfp_nsp_has_stored_fw_load (struct nfp_nsp*) ; 
 int /*<<< orphan*/  nfp_printk (char const*,int /*<<< orphan*/ ,char*,char const* const,...) ; 

__attribute__((used)) static void nfp_nsp_load_fw_extended_msg(struct nfp_nsp *state, u32 ret_val)
{
	static const char * const major_msg[] = {
		/* 0 */ "Firmware from driver loaded",
		/* 1 */ "Firmware from flash loaded",
		/* 2 */ "Firmware loading failure",
	};
	static const char * const minor_msg[] = {
		/*  0 */ "",
		/*  1 */ "no named partition on flash",
		/*  2 */ "error reading from flash",
		/*  3 */ "can not deflate",
		/*  4 */ "not a trusted file",
		/*  5 */ "can not parse FW file",
		/*  6 */ "MIP not found in FW file",
		/*  7 */ "null firmware name in MIP",
		/*  8 */ "FW version none",
		/*  9 */ "FW build number none",
		/* 10 */ "no FW selection policy HWInfo key found",
		/* 11 */ "static FW selection policy",
		/* 12 */ "FW version has precedence",
		/* 13 */ "different FW application load requested",
		/* 14 */ "development build",
	};
	unsigned int major, minor;
	const char *level;

	major = FIELD_GET(NFP_FW_LOAD_RET_MAJOR, ret_val);
	minor = FIELD_GET(NFP_FW_LOAD_RET_MINOR, ret_val);

	if (!nfp_nsp_has_stored_fw_load(state))
		return;

	/* Lower the message level in legacy case */
	if (major == 0 && (minor == 0 || minor == 10))
		level = KERN_DEBUG;
	else if (major == 2)
		level = KERN_ERR;
	else
		level = KERN_INFO;

	if (major >= ARRAY_SIZE(major_msg))
		nfp_printk(level, state->cpp, "FW loading status: %x\n",
			   ret_val);
	else if (minor >= ARRAY_SIZE(minor_msg))
		nfp_printk(level, state->cpp, "%s, reason code: %d\n",
			   major_msg[major], minor);
	else
		nfp_printk(level, state->cpp, "%s%c %s\n",
			   major_msg[major], minor ? ',' : '.',
			   minor_msg[minor]);
}