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
struct anybuss_host {int /*<<< orphan*/  qcache; int /*<<< orphan*/  qthread; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_assert (struct anybuss_host*) ; 

void anybuss_host_common_remove(struct anybuss_host *host)
{
	struct anybuss_host *cd = host;

	device_unregister(&cd->client->dev);
	kthread_stop(cd->qthread);
	reset_assert(cd);
	kmem_cache_destroy(cd->qcache);
}