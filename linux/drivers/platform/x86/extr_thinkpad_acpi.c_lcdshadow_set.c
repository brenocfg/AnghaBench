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
 int lcdshadow_on_off (int) ; 
 int lcdshadow_state ; 

__attribute__((used)) static int lcdshadow_set(bool on)
{
	if (lcdshadow_state < 0)
		return lcdshadow_state;
	if (lcdshadow_state == on)
		return 0;
	return lcdshadow_on_off(on);
}