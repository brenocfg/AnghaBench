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
 int /*<<< orphan*/  TIF_ADDR32 ; 
 int /*<<< orphan*/  __set_personality_ia32 () ; 
 int /*<<< orphan*/  __set_personality_x32 () ; 
 int /*<<< orphan*/  set_thread_flag (int /*<<< orphan*/ ) ; 

void set_personality_ia32(bool x32)
{
	/* Make sure to be in 32bit mode */
	set_thread_flag(TIF_ADDR32);

	if (x32)
		__set_personality_x32();
	else
		__set_personality_ia32();
}