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
struct cnic_local {int /*<<< orphan*/  bnx2x_igu_sb_id; } ;
struct cnic_dev {struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSTORM_ID ; 
 int /*<<< orphan*/  IGU_INT_DISABLE ; 
 int /*<<< orphan*/  cnic_ack_bnx2x_int (struct cnic_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cnic_ack_bnx2x_msix(struct cnic_dev *dev)
{
	struct cnic_local *cp = dev->cnic_priv;

	cnic_ack_bnx2x_int(dev, cp->bnx2x_igu_sb_id, CSTORM_ID, 0,
			   IGU_INT_DISABLE, 0);
}