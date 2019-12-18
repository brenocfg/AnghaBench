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
struct TYPE_2__ {int chip; int /*<<< orphan*/  name; } ;
struct brcmf_chip_priv {TYPE_1__ pub; } ;

/* Variables and functions */
#define  BRCM_CC_4335_CHIP_ID 146 
#define  BRCM_CC_4339_CHIP_ID 145 
#define  BRCM_CC_4345_CHIP_ID 144 
#define  BRCM_CC_43465_CHIP_ID 143 
#define  BRCM_CC_4350_CHIP_ID 142 
#define  BRCM_CC_43525_CHIP_ID 141 
#define  BRCM_CC_4354_CHIP_ID 140 
#define  BRCM_CC_43567_CHIP_ID 139 
#define  BRCM_CC_43569_CHIP_ID 138 
#define  BRCM_CC_4356_CHIP_ID 137 
#define  BRCM_CC_43570_CHIP_ID 136 
#define  BRCM_CC_4358_CHIP_ID 135 
#define  BRCM_CC_4359_CHIP_ID 134 
#define  BRCM_CC_43602_CHIP_ID 133 
#define  BRCM_CC_4365_CHIP_ID 132 
#define  BRCM_CC_43664_CHIP_ID 131 
#define  BRCM_CC_4366_CHIP_ID 130 
#define  BRCM_CC_4371_CHIP_ID 129 
#define  CY_CC_4373_CHIP_ID 128 
 int /*<<< orphan*/  brcmf_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 brcmf_chip_tcm_rambase(struct brcmf_chip_priv *ci)
{
	switch (ci->pub.chip) {
	case BRCM_CC_4345_CHIP_ID:
		return 0x198000;
	case BRCM_CC_4335_CHIP_ID:
	case BRCM_CC_4339_CHIP_ID:
	case BRCM_CC_4350_CHIP_ID:
	case BRCM_CC_4354_CHIP_ID:
	case BRCM_CC_4356_CHIP_ID:
	case BRCM_CC_43567_CHIP_ID:
	case BRCM_CC_43569_CHIP_ID:
	case BRCM_CC_43570_CHIP_ID:
	case BRCM_CC_4358_CHIP_ID:
	case BRCM_CC_4359_CHIP_ID:
	case BRCM_CC_43602_CHIP_ID:
	case BRCM_CC_4371_CHIP_ID:
		return 0x180000;
	case BRCM_CC_43465_CHIP_ID:
	case BRCM_CC_43525_CHIP_ID:
	case BRCM_CC_4365_CHIP_ID:
	case BRCM_CC_4366_CHIP_ID:
	case BRCM_CC_43664_CHIP_ID:
		return 0x200000;
	case CY_CC_4373_CHIP_ID:
		return 0x160000;
	default:
		brcmf_err("unknown chip: %s\n", ci->pub.name);
		break;
	}
	return 0;
}