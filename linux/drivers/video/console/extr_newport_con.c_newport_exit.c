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
 int MAX_NR_CONSOLES ; 
 int /*<<< orphan*/  newport_set_def_font (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void newport_exit(void)
{
	int i;

	/* free memory used by user font */
	for (i = 0; i < MAX_NR_CONSOLES; i++)
		newport_set_def_font(i, NULL);
}