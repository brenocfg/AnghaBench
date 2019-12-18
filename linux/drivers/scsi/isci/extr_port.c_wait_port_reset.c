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
struct isci_port {int /*<<< orphan*/  state; } ;
struct isci_host {int /*<<< orphan*/  eventq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPORT_RESET_PENDING ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wait_port_reset(struct isci_host *ihost, struct isci_port *iport)
{
	wait_event(ihost->eventq, !test_bit(IPORT_RESET_PENDING, &iport->state));
}