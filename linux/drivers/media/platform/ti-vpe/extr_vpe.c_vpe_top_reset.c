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
struct vpe_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPE_CLK_RESET ; 
 int /*<<< orphan*/  VPE_DATA_PATH_CLK_RESET_MASK ; 
 int /*<<< orphan*/  VPE_DATA_PATH_CLK_RESET_SHIFT ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  write_field_reg (struct vpe_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vpe_top_reset(struct vpe_dev *dev)
{

	write_field_reg(dev, VPE_CLK_RESET, 1, VPE_DATA_PATH_CLK_RESET_MASK,
		VPE_DATA_PATH_CLK_RESET_SHIFT);

	usleep_range(100, 150);

	write_field_reg(dev, VPE_CLK_RESET, 0, VPE_DATA_PATH_CLK_RESET_MASK,
		VPE_DATA_PATH_CLK_RESET_SHIFT);
}