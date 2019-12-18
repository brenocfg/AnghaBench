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
struct TYPE_2__ {void* lsi_ptr; } ;

/* Variables and functions */
 TYPE_1__ ap_airq ; 
 scalar_t__ ap_using_interrupts () ; 

void *ap_airq_ptr(void)
{
	if (ap_using_interrupts())
		return ap_airq.lsi_ptr;
	return NULL;
}