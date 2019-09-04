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
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  ug_io_base ; 
 int /*<<< orphan*/  ug_is_txfifo_ready () ; 
 int /*<<< orphan*/  ug_raw_putc (char) ; 

__attribute__((used)) static void ug_putc(char ch)
{
	int count = 16;

	if (!ug_io_base)
		return;

	while (!ug_is_txfifo_ready() && count--)
		barrier();
	if (count >= 0)
		ug_raw_putc(ch);
}