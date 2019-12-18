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
struct tifm_adapter {unsigned int num_sockets; int /*<<< orphan*/  dev; int /*<<< orphan*/  id; TYPE_1__** sockets; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tifm_adapter_idr ; 
 int /*<<< orphan*/  tifm_adapter_lock ; 
 int /*<<< orphan*/  workqueue ; 

void tifm_remove_adapter(struct tifm_adapter *fm)
{
	unsigned int cnt;

	flush_workqueue(workqueue);
	for (cnt = 0; cnt < fm->num_sockets; ++cnt) {
		if (fm->sockets[cnt])
			device_unregister(&fm->sockets[cnt]->dev);
	}

	spin_lock(&tifm_adapter_lock);
	idr_remove(&tifm_adapter_idr, fm->id);
	spin_unlock(&tifm_adapter_lock);
	device_del(&fm->dev);
}