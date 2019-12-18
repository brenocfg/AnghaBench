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
struct hvsi_struct {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ HVSI_OPEN ; 
 scalar_t__ HVSI_WAIT_FOR_MCTRL_RESPONSE ; 

__attribute__((used)) static inline int is_open(struct hvsi_struct *hp)
{
	/* if we're waiting for an mctrl then we're already open */
	return (hp->state == HVSI_OPEN)
			|| (hp->state == HVSI_WAIT_FOR_MCTRL_RESPONSE);
}