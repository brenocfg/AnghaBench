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
typedef  int s8 ;

/* Variables and functions */
#define  BOND_LINK_BACK 131 
#define  BOND_LINK_DOWN 130 
#define  BOND_LINK_FAIL 129 
#define  BOND_LINK_UP 128 

const char *bond_slave_link_status(s8 link)
{
	switch (link) {
	case BOND_LINK_UP:
		return "up";
	case BOND_LINK_FAIL:
		return "going down";
	case BOND_LINK_DOWN:
		return "down";
	case BOND_LINK_BACK:
		return "going back";
	default:
		return "unknown";
	}
}