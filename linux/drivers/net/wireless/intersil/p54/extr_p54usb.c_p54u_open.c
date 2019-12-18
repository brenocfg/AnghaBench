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
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int p54u_init_urbs (struct ieee80211_hw*) ; 

__attribute__((used)) static int p54u_open(struct ieee80211_hw *dev)
{
	/*
	 * TODO: Because we don't know how to reliably stop the 3887 and
	 * the isl3886+net2280, other than brutally cut off all
	 * communications. We have to reinitialize the urbs on every start.
	 */
	return p54u_init_urbs(dev);
}