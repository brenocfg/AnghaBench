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
struct dwc3_ep {int /*<<< orphan*/  trb_dequeue; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwc3_ep_inc_trb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dwc3_ep_inc_deq(struct dwc3_ep *dep)
{
	dwc3_ep_inc_trb(&dep->trb_dequeue);
}