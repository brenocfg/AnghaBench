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
 int /*<<< orphan*/  __vmclrmap (int /*<<< orphan*/ ,int) ; 

void tlb_flush_all(void)
{
	/*  should probably use that fixaddr end or whateve label  */
	__vmclrmap(0, 0xffff0000);
}