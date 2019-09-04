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
struct ucc_geth {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
uec_get_regs_len(struct net_device *netdev)
{
	return sizeof(struct ucc_geth);
}