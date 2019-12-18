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
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int EXPO_CHANGE ; 
 int LATENT_CHANGE ; 
 int /*<<< orphan*/  R00_PART_CONTROL ; 
 int /*<<< orphan*/  R0E_AD_HEIGHTL ; 
 int /*<<< orphan*/  R0F_AD_HEIGHTH ; 
 int /*<<< orphan*/  R10_AD_COL_BEGINL ; 
 int /*<<< orphan*/  R11_AD_COL_BEGINH ; 
 int /*<<< orphan*/  R14_AD_ROW_BEGINL ; 
 int /*<<< orphan*/  R1C_AD_EXPOSE_TIMEL ; 
 int /*<<< orphan*/  R3B_Test3 ; 
 int /*<<< orphan*/  R91_AD_SLOPEREG ; 
 int /*<<< orphan*/  R94_AD_BITCONTROL ; 
 int /*<<< orphan*/  reg_w1 (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_w2 (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tv_8532_setReg(struct gspca_dev *gspca_dev)
{
	reg_w1(gspca_dev, R3B_Test3, 0x0a);	/* Test0Sel = 10 */
	/******************************************************/
	reg_w1(gspca_dev, R0E_AD_HEIGHTL, 0x90);
	reg_w1(gspca_dev, R0F_AD_HEIGHTH, 0x01);
	reg_w2(gspca_dev, R1C_AD_EXPOSE_TIMEL, 0x018f);
	reg_w1(gspca_dev, R10_AD_COL_BEGINL, 0x44);
						/* begin active line */
	reg_w1(gspca_dev, R11_AD_COL_BEGINH, 0x00);
						/* mirror and digital gain */
	reg_w1(gspca_dev, R14_AD_ROW_BEGINL, 0x0a);

	reg_w1(gspca_dev, R94_AD_BITCONTROL, 0x02);
	reg_w1(gspca_dev, R91_AD_SLOPEREG, 0x00);
	reg_w1(gspca_dev, R00_PART_CONTROL, LATENT_CHANGE | EXPO_CHANGE);
						/* = 0x84 */
}