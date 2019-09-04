#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* assert_event ) (unsigned int) ;} ;

/* Variables and functions */
 TYPE_1__ soc_ops ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 

void soc_assert_event(unsigned int evt)
{
	if (soc_ops.assert_event)
		soc_ops.assert_event(evt);
}