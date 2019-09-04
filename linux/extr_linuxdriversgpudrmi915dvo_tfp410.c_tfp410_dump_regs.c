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
typedef  int /*<<< orphan*/  u8 ;
struct intel_dvo_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  TFP410_CTL_1 ; 
 int /*<<< orphan*/  TFP410_CTL_2 ; 
 int /*<<< orphan*/  TFP410_CTL_3 ; 
 int /*<<< orphan*/  TFP410_DE_CNT_HI ; 
 int /*<<< orphan*/  TFP410_DE_CNT_LO ; 
 int /*<<< orphan*/  TFP410_DE_CTL ; 
 int /*<<< orphan*/  TFP410_DE_DLY ; 
 int /*<<< orphan*/  TFP410_DE_LIN_HI ; 
 int /*<<< orphan*/  TFP410_DE_LIN_LO ; 
 int /*<<< orphan*/  TFP410_DE_TOP ; 
 int /*<<< orphan*/  TFP410_H_RES_HI ; 
 int /*<<< orphan*/  TFP410_H_RES_LO ; 
 int /*<<< orphan*/  TFP410_REV ; 
 int /*<<< orphan*/  TFP410_USERCFG ; 
 int /*<<< orphan*/  TFP410_V_RES_HI ; 
 int /*<<< orphan*/  TFP410_V_RES_LO ; 
 int /*<<< orphan*/  tfp410_readb (struct intel_dvo_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tfp410_dump_regs(struct intel_dvo_device *dvo)
{
	u8 val, val2;

	tfp410_readb(dvo, TFP410_REV, &val);
	DRM_DEBUG_KMS("TFP410_REV: 0x%02X\n", val);
	tfp410_readb(dvo, TFP410_CTL_1, &val);
	DRM_DEBUG_KMS("TFP410_CTL1: 0x%02X\n", val);
	tfp410_readb(dvo, TFP410_CTL_2, &val);
	DRM_DEBUG_KMS("TFP410_CTL2: 0x%02X\n", val);
	tfp410_readb(dvo, TFP410_CTL_3, &val);
	DRM_DEBUG_KMS("TFP410_CTL3: 0x%02X\n", val);
	tfp410_readb(dvo, TFP410_USERCFG, &val);
	DRM_DEBUG_KMS("TFP410_USERCFG: 0x%02X\n", val);
	tfp410_readb(dvo, TFP410_DE_DLY, &val);
	DRM_DEBUG_KMS("TFP410_DE_DLY: 0x%02X\n", val);
	tfp410_readb(dvo, TFP410_DE_CTL, &val);
	DRM_DEBUG_KMS("TFP410_DE_CTL: 0x%02X\n", val);
	tfp410_readb(dvo, TFP410_DE_TOP, &val);
	DRM_DEBUG_KMS("TFP410_DE_TOP: 0x%02X\n", val);
	tfp410_readb(dvo, TFP410_DE_CNT_LO, &val);
	tfp410_readb(dvo, TFP410_DE_CNT_HI, &val2);
	DRM_DEBUG_KMS("TFP410_DE_CNT: 0x%02X%02X\n", val2, val);
	tfp410_readb(dvo, TFP410_DE_LIN_LO, &val);
	tfp410_readb(dvo, TFP410_DE_LIN_HI, &val2);
	DRM_DEBUG_KMS("TFP410_DE_LIN: 0x%02X%02X\n", val2, val);
	tfp410_readb(dvo, TFP410_H_RES_LO, &val);
	tfp410_readb(dvo, TFP410_H_RES_HI, &val2);
	DRM_DEBUG_KMS("TFP410_H_RES: 0x%02X%02X\n", val2, val);
	tfp410_readb(dvo, TFP410_V_RES_LO, &val);
	tfp410_readb(dvo, TFP410_V_RES_HI, &val2);
	DRM_DEBUG_KMS("TFP410_V_RES: 0x%02X%02X\n", val2, val);
}