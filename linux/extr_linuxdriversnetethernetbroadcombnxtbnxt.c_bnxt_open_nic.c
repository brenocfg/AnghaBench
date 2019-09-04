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
 int __bnxt_open_nic (struct bnxt*,int,int) ; 
 int /*<<< orphan*/  dev_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 

int bnxt_open_nic(struct bnxt *bp, bool irq_re_init, bool link_re_init)
{
	int rc = 0;

	rc = __bnxt_open_nic(bp, irq_re_init, link_re_init);
	if (rc) {
		netdev_err(bp->dev, "nic open fail (rc: %x)\n", rc);
		dev_close(bp->dev);
	}
	return rc;
}