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
 int IONIC_DEV_CMD_REG_COUNT ; 
 int IONIC_DEV_INFO_REG_COUNT ; 

__attribute__((used)) static int ionic_get_regs_len(struct net_device *netdev)
{
	return (IONIC_DEV_INFO_REG_COUNT + IONIC_DEV_CMD_REG_COUNT) * sizeof(u32);
}