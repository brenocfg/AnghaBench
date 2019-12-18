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
typedef  int u8 ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  NCT6102D_WDT_CONTROL ; 
 int /*<<< orphan*/  NCT6102D_WDT_CSR ; 
 int /*<<< orphan*/  NCT6102D_WDT_TIMEOUT ; 
#define  NCT6102_ID 149 
#define  NCT6775_ID 148 
#define  NCT6776_ID 147 
#define  NCT6779_ID 146 
#define  NCT6791_ID 145 
#define  NCT6792_ID 144 
#define  NCT6793_ID 143 
#define  NCT6795_ID 142 
#define  NCT6796_ID 141 
#define  W83627DHG_ID 140 
#define  W83627DHG_P_ID 139 
#define  W83627EHF_ID 138 
#define  W83627HF_ID 137 
 int /*<<< orphan*/  W83627HF_LD_WDT ; 
 int /*<<< orphan*/  W83627HF_WDT_CONTROL ; 
 int /*<<< orphan*/  W83627HF_WDT_TIMEOUT ; 
#define  W83627S_ID 136 
#define  W83627THF_ID 135 
#define  W83627UHG_ID 134 
#define  W83637HF_ID 133 
#define  W83667HG_B_ID 132 
#define  W83667HG_ID 131 
#define  W83687THF_ID 130 
#define  W83697HF_ID 129 
 int /*<<< orphan*/  W83697HF_WDT_CONTROL ; 
 int /*<<< orphan*/  W83697HF_WDT_TIMEOUT ; 
#define  W83697UG_ID 128 
 int /*<<< orphan*/  W836X7HF_WDT_CSR ; 
 int /*<<< orphan*/  cr_wdt_control ; 
 int /*<<< orphan*/  cr_wdt_csr ; 
 int /*<<< orphan*/  cr_wdt_timeout ; 
 int nct6102 ; 
 int nct6775 ; 
 int nct6776 ; 
 int nct6779 ; 
 int nct6791 ; 
 int nct6792 ; 
 int nct6793 ; 
 int nct6795 ; 
 int nct6796 ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int superio_enter () ; 
 int /*<<< orphan*/  superio_exit () ; 
 int superio_inb (int) ; 
 int /*<<< orphan*/  superio_select (int /*<<< orphan*/ ) ; 
 int w83627dhg ; 
 int w83627dhg_p ; 
 int w83627ehf ; 
 int w83627hf ; 
 int w83627s ; 
 int w83627thf ; 
 int w83627uhg ; 
 int w83637hf ; 
 int w83667hg ; 
 int w83667hg_b ; 
 int w83687thf ; 
 int w83697hf ; 
 int w83697ug ; 

__attribute__((used)) static int wdt_find(int addr)
{
	u8 val;
	int ret;

	cr_wdt_timeout = W83627HF_WDT_TIMEOUT;
	cr_wdt_control = W83627HF_WDT_CONTROL;
	cr_wdt_csr = W836X7HF_WDT_CSR;

	ret = superio_enter();
	if (ret)
		return ret;
	superio_select(W83627HF_LD_WDT);
	val = superio_inb(0x20);
	switch (val) {
	case W83627HF_ID:
		ret = w83627hf;
		break;
	case W83627S_ID:
		ret = w83627s;
		break;
	case W83697HF_ID:
		ret = w83697hf;
		cr_wdt_timeout = W83697HF_WDT_TIMEOUT;
		cr_wdt_control = W83697HF_WDT_CONTROL;
		break;
	case W83697UG_ID:
		ret = w83697ug;
		cr_wdt_timeout = W83697HF_WDT_TIMEOUT;
		cr_wdt_control = W83697HF_WDT_CONTROL;
		break;
	case W83637HF_ID:
		ret = w83637hf;
		break;
	case W83627THF_ID:
		ret = w83627thf;
		break;
	case W83687THF_ID:
		ret = w83687thf;
		break;
	case W83627EHF_ID:
		ret = w83627ehf;
		break;
	case W83627DHG_ID:
		ret = w83627dhg;
		break;
	case W83627DHG_P_ID:
		ret = w83627dhg_p;
		break;
	case W83627UHG_ID:
		ret = w83627uhg;
		break;
	case W83667HG_ID:
		ret = w83667hg;
		break;
	case W83667HG_B_ID:
		ret = w83667hg_b;
		break;
	case NCT6775_ID:
		ret = nct6775;
		break;
	case NCT6776_ID:
		ret = nct6776;
		break;
	case NCT6779_ID:
		ret = nct6779;
		break;
	case NCT6791_ID:
		ret = nct6791;
		break;
	case NCT6792_ID:
		ret = nct6792;
		break;
	case NCT6793_ID:
		ret = nct6793;
		break;
	case NCT6795_ID:
		ret = nct6795;
		break;
	case NCT6796_ID:
		ret = nct6796;
		break;
	case NCT6102_ID:
		ret = nct6102;
		cr_wdt_timeout = NCT6102D_WDT_TIMEOUT;
		cr_wdt_control = NCT6102D_WDT_CONTROL;
		cr_wdt_csr = NCT6102D_WDT_CSR;
		break;
	case 0xff:
		ret = -ENODEV;
		break;
	default:
		ret = -ENODEV;
		pr_err("Unsupported chip ID: 0x%02x\n", val);
		break;
	}
	superio_exit();
	return ret;
}