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
struct service_processor {int dummy; } ;
struct reverse_heartbeat {scalar_t__ stopped; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 

void ibmasm_init_reverse_heartbeat(struct service_processor *sp, struct reverse_heartbeat *rhb)
{
	init_waitqueue_head(&rhb->wait);
	rhb->stopped = 0;
}