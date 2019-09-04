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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EMAC_MAX_REG_SIZE ; 

__attribute__((used)) static int emac_get_regs_len(struct net_device *netdev)
{
	return EMAC_MAX_REG_SIZE * sizeof(u32);
}