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
typedef  int u16 ;

/* Variables and functions */
 int LINK_WIDTH_DEFAULT ; 

u16 tx_link_width(u16 link_width)
{
	int n = LINK_WIDTH_DEFAULT;
	u16 tx_width = n;

	while (link_width && n) {
		if (link_width & (1 << (n - 1))) {
			tx_width = n;
			break;
		}
		n--;
	}

	return tx_width;
}