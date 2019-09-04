#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct dnet {TYPE_1__* dev; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {scalar_t__ dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DNET_INTERNAL_MAC_ADDR_0_REG ; 
 int /*<<< orphan*/  DNET_INTERNAL_MAC_ADDR_1_REG ; 
 int /*<<< orphan*/  DNET_INTERNAL_MAC_ADDR_2_REG ; 
 int /*<<< orphan*/  be16_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dnet_writew_mac (struct dnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __dnet_set_hwaddr(struct dnet *bp)
{
	u16 tmp;

	tmp = be16_to_cpup((__be16 *)bp->dev->dev_addr);
	dnet_writew_mac(bp, DNET_INTERNAL_MAC_ADDR_0_REG, tmp);
	tmp = be16_to_cpup((__be16 *)(bp->dev->dev_addr + 2));
	dnet_writew_mac(bp, DNET_INTERNAL_MAC_ADDR_1_REG, tmp);
	tmp = be16_to_cpup((__be16 *)(bp->dev->dev_addr + 4));
	dnet_writew_mac(bp, DNET_INTERNAL_MAC_ADDR_2_REG, tmp);
}