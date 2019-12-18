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
struct ravb_private {int addr; } ;
struct net_device {int dummy; } ;
typedef  enum ravb_reg { ____Placeholder_ravb_reg } ravb_reg ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int) ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static inline void ravb_write(struct net_device *ndev, u32 data,
			      enum ravb_reg reg)
{
	struct ravb_private *priv = netdev_priv(ndev);

	iowrite32(data, priv->addr + reg);
}