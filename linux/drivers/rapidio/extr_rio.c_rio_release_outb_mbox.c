#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rio_mport {TYPE_2__* outb_msg; TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/ * res; int /*<<< orphan*/ * mcback; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* close_outb_mbox ) (struct rio_mport*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int release_resource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct rio_mport*,int) ; 

int rio_release_outb_mbox(struct rio_mport *mport, int mbox)
{
	int rc;

	if (!mport->ops->close_outb_mbox || !mport->outb_msg[mbox].res)
		return -EINVAL;

	mport->ops->close_outb_mbox(mport, mbox);
	mport->outb_msg[mbox].mcback = NULL;

	rc = release_resource(mport->outb_msg[mbox].res);
	if (rc)
		return rc;

	kfree(mport->outb_msg[mbox].res);
	mport->outb_msg[mbox].res = NULL;

	return 0;
}