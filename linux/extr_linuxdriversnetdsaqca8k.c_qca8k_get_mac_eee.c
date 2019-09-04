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
struct ethtool_eee {int dummy; } ;
struct dsa_switch {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
qca8k_get_mac_eee(struct dsa_switch *ds, int port, struct ethtool_eee *e)
{
	/* Nothing to do on the port's MAC */
	return 0;
}