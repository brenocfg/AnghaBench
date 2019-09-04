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
 int MAX_RCV_WND ; 

__attribute__((used)) static unsigned int select_rcv_wscale(int space, int wscale_ok, int win_clamp)
{
	int wscale = 0;

	if (space > MAX_RCV_WND)
		space = MAX_RCV_WND;
	if (win_clamp && win_clamp < space)
		space = win_clamp;

	if (wscale_ok) {
		while (wscale < 14 && (65535 << wscale) < space)
			wscale++;
	}
	return wscale;
}