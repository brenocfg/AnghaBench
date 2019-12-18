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
 int PORTADDR_ENH ; 
 int /*<<< orphan*/  PORTADR (unsigned int) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int aha1740_test_port(unsigned int base)
{
	if ( inb(PORTADR(base)) & PORTADDR_ENH )
		return 1;   /* Okay, we're all set */
	
	printk("aha174x: Board detected, but not in enhanced mode, so disabled it.\n");
	return 0;
}