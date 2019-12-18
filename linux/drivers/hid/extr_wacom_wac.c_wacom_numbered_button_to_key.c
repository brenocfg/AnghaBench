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
 int BTN_0 ; 
 int BTN_A ; 
 int BTN_BASE ; 

__attribute__((used)) static int wacom_numbered_button_to_key(int n)
{
	if (n < 10)
		return BTN_0 + n;
	else if (n < 16)
		return BTN_A + (n-10);
	else if (n < 18)
		return BTN_BASE + (n-16);
	else
		return 0;
}