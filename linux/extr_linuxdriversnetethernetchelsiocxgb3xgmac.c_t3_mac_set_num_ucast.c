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
struct cmac {int nucast; } ;

/* Variables and functions */
 int EINVAL ; 
 int EXACT_ADDR_FILTERS ; 

int t3_mac_set_num_ucast(struct cmac *mac, int n)
{
	if (n > EXACT_ADDR_FILTERS)
		return -EINVAL;
	mac->nucast = n;
	return 0;
}