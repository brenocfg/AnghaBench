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
struct gb_svc {int /*<<< orphan*/  wq; int /*<<< orphan*/  device_id_map; scalar_t__ connection; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_connection_destroy (scalar_t__) ; 
 int /*<<< orphan*/  ida_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct gb_svc*) ; 
 struct gb_svc* to_gb_svc (struct device*) ; 

__attribute__((used)) static void gb_svc_release(struct device *dev)
{
	struct gb_svc *svc = to_gb_svc(dev);

	if (svc->connection)
		gb_connection_destroy(svc->connection);
	ida_destroy(&svc->device_id_map);
	destroy_workqueue(svc->wq);
	kfree(svc);
}