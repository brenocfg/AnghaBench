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
 int /*<<< orphan*/  WDT_START ; 
 int /*<<< orphan*/  ibwdt_lock ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int timeout ; 

__attribute__((used)) static void ibwdt_ping(void)
{
	int wd_margin = 15 - ((timeout + 1) / 2);

	spin_lock(&ibwdt_lock);

	/* Write a watchdog value */
	outb_p(wd_margin, WDT_START);

	spin_unlock(&ibwdt_lock);
}