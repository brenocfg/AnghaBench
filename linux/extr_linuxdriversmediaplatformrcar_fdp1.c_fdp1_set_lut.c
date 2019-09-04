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
struct fdp1_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FD1_LUT_BLD_GAIN ; 
 int /*<<< orphan*/  FD1_LUT_DIF_ADJ ; 
 int /*<<< orphan*/  FD1_LUT_DIF_GAIN ; 
 int /*<<< orphan*/  FD1_LUT_MDET ; 
 int /*<<< orphan*/  FD1_LUT_SAD_ADJ ; 
 int /*<<< orphan*/  fdp1_bld_gain ; 
 int /*<<< orphan*/  fdp1_dif_gain ; 
 int /*<<< orphan*/  fdp1_diff_adj ; 
 int /*<<< orphan*/  fdp1_mdet ; 
 int /*<<< orphan*/  fdp1_sad_adj ; 
 int /*<<< orphan*/  fdp1_write_lut (struct fdp1_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fdp1_set_lut(struct fdp1_dev *fdp1)
{
	fdp1_write_lut(fdp1, fdp1_diff_adj, ARRAY_SIZE(fdp1_diff_adj),
			FD1_LUT_DIF_ADJ);
	fdp1_write_lut(fdp1, fdp1_sad_adj,  ARRAY_SIZE(fdp1_sad_adj),
			FD1_LUT_SAD_ADJ);
	fdp1_write_lut(fdp1, fdp1_bld_gain, ARRAY_SIZE(fdp1_bld_gain),
			FD1_LUT_BLD_GAIN);
	fdp1_write_lut(fdp1, fdp1_dif_gain, ARRAY_SIZE(fdp1_dif_gain),
			FD1_LUT_DIF_GAIN);
	fdp1_write_lut(fdp1, fdp1_mdet, ARRAY_SIZE(fdp1_mdet),
			FD1_LUT_MDET);
}