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
struct pxa_udc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WAIT_FOR_SETUP ; 
 int /*<<< orphan*/  set_ep0state (struct pxa_udc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ep0_idle(struct pxa_udc *dev)
{
	set_ep0state(dev, WAIT_FOR_SETUP);
}