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
typedef  scalar_t__ u_long ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct hp100_private {scalar_t__ whatever_offset; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 struct hp100_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static inline dma_addr_t virt_to_whatever(struct net_device *dev, u32 * ptr)
{
	struct hp100_private *lp = netdev_priv(dev);
	return ((u_long) ptr) + lp->whatever_offset;
}