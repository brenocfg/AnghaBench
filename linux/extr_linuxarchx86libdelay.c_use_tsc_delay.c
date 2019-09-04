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

/* Variables and functions */
 scalar_t__ delay_fn ; 
 scalar_t__ delay_loop ; 
 scalar_t__ delay_tsc ; 

void use_tsc_delay(void)
{
	if (delay_fn == delay_loop)
		delay_fn = delay_tsc;
}