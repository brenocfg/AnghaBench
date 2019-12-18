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
struct shim_service {int /*<<< orphan*/  callback_param; int /*<<< orphan*/  callback; int /*<<< orphan*/  queue; } ;
struct service_creation {int /*<<< orphan*/  callback_param; int /*<<< orphan*/  callback; } ;
typedef  int /*<<< orphan*/  VCHIQ_INSTANCE_T ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct shim_service*) ; 
 struct shim_service* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ vchiu_queue_init (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct shim_service *service_alloc(VCHIQ_INSTANCE_T instance,
	struct service_creation *setup)
{
	struct shim_service *service = kzalloc(sizeof(struct shim_service), GFP_KERNEL);

	(void)instance;

	if (service) {
		if (vchiu_queue_init(&service->queue, 64)) {
			service->callback = setup->callback;
			service->callback_param = setup->callback_param;
		} else {
			kfree(service);
			service = NULL;
		}
	}

	return service;
}