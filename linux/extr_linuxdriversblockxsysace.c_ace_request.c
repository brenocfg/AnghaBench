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
struct request_queue {int dummy; } ;
struct request {TYPE_1__* rq_disk; } ;
struct ace_device {int /*<<< orphan*/  fsm_tasklet; } ;
struct TYPE_2__ {struct ace_device* private_data; } ;

/* Variables and functions */
 struct request* ace_get_next_request (struct request_queue*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ace_request(struct request_queue * q)
{
	struct request *req;
	struct ace_device *ace;

	req = ace_get_next_request(q);

	if (req) {
		ace = req->rq_disk->private_data;
		tasklet_schedule(&ace->fsm_tasklet);
	}
}