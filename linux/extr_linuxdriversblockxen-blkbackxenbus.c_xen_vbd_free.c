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
struct xen_vbd {int /*<<< orphan*/ * bdev; scalar_t__ readonly; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMODE_READ ; 
 int /*<<< orphan*/  FMODE_WRITE ; 
 int /*<<< orphan*/  blkdev_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xen_vbd_free(struct xen_vbd *vbd)
{
	if (vbd->bdev)
		blkdev_put(vbd->bdev, vbd->readonly ? FMODE_READ : FMODE_WRITE);
	vbd->bdev = NULL;
}