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
struct gmac_max_framelen {int max_l3_len; int val; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct gmac_max_framelen*) ; 
 unsigned int ETH_HLEN ; 
 unsigned int VLAN_HLEN ; 
 struct gmac_max_framelen* gmac_maxlens ; 

__attribute__((used)) static int gmac_pick_rx_max_len(unsigned int max_l3_len)
{
	const struct gmac_max_framelen *maxlen;
	int maxtot;
	int i;

	maxtot = max_l3_len + ETH_HLEN + VLAN_HLEN;

	for (i = 0; i < ARRAY_SIZE(gmac_maxlens); i++) {
		maxlen = &gmac_maxlens[i];
		if (maxtot <= maxlen->max_l3_len)
			return maxlen->val;
	}

	return -1;
}