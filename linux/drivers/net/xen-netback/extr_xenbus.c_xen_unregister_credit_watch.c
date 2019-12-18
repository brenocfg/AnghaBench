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
struct TYPE_2__ {int /*<<< orphan*/ * node; } ;
struct xenvif {TYPE_1__ credit_watch; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_xenbus_watch (TYPE_1__*) ; 

__attribute__((used)) static void xen_unregister_credit_watch(struct xenvif *vif)
{
	if (vif->credit_watch.node) {
		unregister_xenbus_watch(&vif->credit_watch);
		kfree(vif->credit_watch.node);
		vif->credit_watch.node = NULL;
	}
}