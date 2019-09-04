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
struct cnic_local {int /*<<< orphan*/  bnx2x_igu_sb_id; } ;
struct cnic_dev {struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGU_INT_ENABLE ; 
 int /*<<< orphan*/  IGU_SEG_ACCESS_DEF ; 
 int /*<<< orphan*/  cnic_ack_igu_sb (struct cnic_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cnic_arm_bnx2x_e2_msix(struct cnic_dev *dev, u32 idx)
{
	struct cnic_local *cp = dev->cnic_priv;

	cnic_ack_igu_sb(dev, cp->bnx2x_igu_sb_id, IGU_SEG_ACCESS_DEF, idx,
			IGU_INT_ENABLE, 1);
}