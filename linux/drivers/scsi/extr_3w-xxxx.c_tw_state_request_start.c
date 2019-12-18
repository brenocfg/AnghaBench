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
struct TYPE_3__ {int* free_queue; size_t free_head; int /*<<< orphan*/ * state; } ;
typedef  TYPE_1__ TW_Device_Extension ;

/* Variables and functions */
 int TW_Q_LENGTH ; 
 int /*<<< orphan*/  TW_S_STARTED ; 

__attribute__((used)) static void tw_state_request_start(TW_Device_Extension *tw_dev, int *request_id)
{
	*request_id = tw_dev->free_queue[tw_dev->free_head];
	tw_dev->free_head = (tw_dev->free_head + 1) % TW_Q_LENGTH;
	tw_dev->state[*request_id] = TW_S_STARTED;
}