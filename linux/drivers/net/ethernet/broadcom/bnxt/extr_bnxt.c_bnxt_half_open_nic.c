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
struct bnxt {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int bnxt_alloc_mem (struct bnxt*,int) ; 
 int /*<<< orphan*/  bnxt_free_mem (struct bnxt*,int) ; 
 int /*<<< orphan*/  bnxt_free_skbs (struct bnxt*) ; 
 int bnxt_init_nic (struct bnxt*,int) ; 
 int /*<<< orphan*/  dev_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 

int bnxt_half_open_nic(struct bnxt *bp)
{
	int rc = 0;

	rc = bnxt_alloc_mem(bp, false);
	if (rc) {
		netdev_err(bp->dev, "bnxt_alloc_mem err: %x\n", rc);
		goto half_open_err;
	}
	rc = bnxt_init_nic(bp, false);
	if (rc) {
		netdev_err(bp->dev, "bnxt_init_nic err: %x\n", rc);
		goto half_open_err;
	}
	return 0;

half_open_err:
	bnxt_free_skbs(bp);
	bnxt_free_mem(bp, false);
	dev_close(bp->dev);
	return rc;
}