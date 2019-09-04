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
 int /*<<< orphan*/  memcons_getc ; 
 int /*<<< orphan*/  memcons_getc_poll ; 
 int /*<<< orphan*/  memcons_putc ; 
 int /*<<< orphan*/  udbg_getc ; 
 int /*<<< orphan*/  udbg_getc_poll ; 
 int /*<<< orphan*/  udbg_putc ; 

void udbg_init_memcons(void)
{
	udbg_putc = memcons_putc;
	udbg_getc = memcons_getc;
	udbg_getc_poll = memcons_getc_poll;
}