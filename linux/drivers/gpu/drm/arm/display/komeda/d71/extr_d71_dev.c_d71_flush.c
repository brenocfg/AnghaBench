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
struct komeda_dev {struct d71_dev* chip_data; } ;
struct d71_dev {int /*<<< orphan*/  gcu_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GCU_CONFIG_CVAL ; 
 int /*<<< orphan*/  GCU_CONFIG_VALID0 ; 
 int /*<<< orphan*/  GCU_CONFIG_VALID1 ; 
 int /*<<< orphan*/  malidp_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void d71_flush(struct komeda_dev *mdev,
		      int master_pipe, u32 active_pipes)
{
	struct d71_dev *d71 = mdev->chip_data;
	u32 reg_offset = (master_pipe == 0) ?
			 GCU_CONFIG_VALID0 : GCU_CONFIG_VALID1;

	malidp_write32(d71->gcu_addr, reg_offset, GCU_CONFIG_CVAL);
}