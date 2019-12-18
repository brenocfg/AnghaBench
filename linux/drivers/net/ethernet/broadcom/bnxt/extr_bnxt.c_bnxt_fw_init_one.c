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
struct bnxt {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int bnxt_approve_mac (struct bnxt*,int /*<<< orphan*/ ,int) ; 
 int bnxt_fw_init_one_p1 (struct bnxt*) ; 
 int bnxt_fw_init_one_p2 (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_fw_init_one_p3 (struct bnxt*) ; 
 int /*<<< orphan*/  netdev_err (TYPE_1__*,char*) ; 

__attribute__((used)) static int bnxt_fw_init_one(struct bnxt *bp)
{
	int rc;

	rc = bnxt_fw_init_one_p1(bp);
	if (rc) {
		netdev_err(bp->dev, "Firmware init phase 1 failed\n");
		return rc;
	}
	rc = bnxt_fw_init_one_p2(bp);
	if (rc) {
		netdev_err(bp->dev, "Firmware init phase 2 failed\n");
		return rc;
	}
	rc = bnxt_approve_mac(bp, bp->dev->dev_addr, false);
	if (rc)
		return rc;
	bnxt_fw_init_one_p3(bp);
	return 0;
}