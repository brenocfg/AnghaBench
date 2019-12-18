#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* free_queue; size_t free_tail; int /*<<< orphan*/ * state; } ;
typedef  TYPE_1__ TW_Device_Extension ;

/* Variables and functions */
 int TW_Q_LENGTH ; 
 int /*<<< orphan*/  TW_S_FINISHED ; 

__attribute__((used)) static void twl_free_request_id(TW_Device_Extension *tw_dev, int request_id)
{
	tw_dev->free_queue[tw_dev->free_tail] = request_id;
	tw_dev->state[request_id] = TW_S_FINISHED;
	tw_dev->free_tail = (tw_dev->free_tail + 1) % TW_Q_LENGTH;
}