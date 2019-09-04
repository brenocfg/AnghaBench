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
struct bnx2x {TYPE_1__* vfdb; } ;
struct TYPE_2__ {struct TYPE_2__* vfs; struct TYPE_2__* vfqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static void __bnx2x_iov_free_vfdb(struct bnx2x *bp)
{
	if (bp->vfdb) {
		kfree(bp->vfdb->vfqs);
		kfree(bp->vfdb->vfs);
		kfree(bp->vfdb);
	}
	bp->vfdb = NULL;
}