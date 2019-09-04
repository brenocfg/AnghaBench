#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct TYPE_4__ {int req_q_index; struct request_queue** RequestQueue; int /*<<< orphan*/  ControllerInitialized; } ;
typedef  TYPE_1__ DAC960_Controller_T ;

/* Variables and functions */
 int DAC960_MaxLogicalDrives ; 
 int /*<<< orphan*/  DAC960_process_queue (TYPE_1__*,struct request_queue*) ; 

__attribute__((used)) static void DAC960_ProcessRequest(DAC960_Controller_T *controller)
{
	int i;

	if (!controller->ControllerInitialized)
		return;

	/* Do this better later! */
	for (i = controller->req_q_index; i < DAC960_MaxLogicalDrives; i++) {
		struct request_queue *req_q = controller->RequestQueue[i];

		if (req_q == NULL)
			continue;

		if (!DAC960_process_queue(controller, req_q)) {
			controller->req_q_index = i;
			return;
		}
	}

	if (controller->req_q_index == 0)
		return;

	for (i = 0; i < controller->req_q_index; i++) {
		struct request_queue *req_q = controller->RequestQueue[i];

		if (req_q == NULL)
			continue;

		if (!DAC960_process_queue(controller, req_q)) {
			controller->req_q_index = i;
			return;
		}
	}
}