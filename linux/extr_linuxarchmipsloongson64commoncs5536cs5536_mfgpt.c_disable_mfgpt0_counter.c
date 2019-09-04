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
 int /*<<< orphan*/  MFGPT0_SETUP ; 
 int inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (int,int /*<<< orphan*/ ) ; 

void disable_mfgpt0_counter(void)
{
	outw(inw(MFGPT0_SETUP) & 0x7fff, MFGPT0_SETUP);
}