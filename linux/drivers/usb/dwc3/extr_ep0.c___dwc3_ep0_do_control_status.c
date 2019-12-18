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
struct dwc3_ep {int dummy; } ;
struct dwc3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_ep0_start_control_status (struct dwc3_ep*) ; 

__attribute__((used)) static void __dwc3_ep0_do_control_status(struct dwc3 *dwc, struct dwc3_ep *dep)
{
	WARN_ON(dwc3_ep0_start_control_status(dep));
}