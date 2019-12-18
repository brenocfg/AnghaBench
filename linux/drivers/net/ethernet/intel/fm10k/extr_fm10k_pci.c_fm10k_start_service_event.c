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
struct fm10k_intfc {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __FM10K_SERVICE_DISABLE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_service_event_schedule (struct fm10k_intfc*) ; 

__attribute__((used)) static void fm10k_start_service_event(struct fm10k_intfc *interface)
{
	clear_bit(__FM10K_SERVICE_DISABLE, interface->state);
	fm10k_service_event_schedule(interface);
}