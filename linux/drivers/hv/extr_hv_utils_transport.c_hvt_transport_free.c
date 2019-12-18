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
struct hvutil_transport {struct hvutil_transport* outmsg; int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hvutil_transport*) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hvt_transport_free(struct hvutil_transport *hvt)
{
	misc_deregister(&hvt->mdev);
	kfree(hvt->outmsg);
	kfree(hvt);
}