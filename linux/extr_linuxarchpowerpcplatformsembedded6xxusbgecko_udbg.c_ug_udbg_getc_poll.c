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
 int ug_getc () ; 
 int /*<<< orphan*/  ug_is_rxfifo_ready () ; 

__attribute__((used)) static int ug_udbg_getc_poll(void)
{
	if (!ug_is_rxfifo_ready())
		return -1;
	return ug_getc();
}