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
struct sfp {unsigned int sm_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  sfp_sm_set_timer (struct sfp*,unsigned int) ; 

__attribute__((used)) static void sfp_sm_next(struct sfp *sfp, unsigned int state,
			unsigned int timeout)
{
	sfp->sm_state = state;
	sfp_sm_set_timer(sfp, timeout);
}