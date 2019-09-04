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
struct net_device {int dummy; } ;
struct nb8800_priv {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ NB8800_MC_INIT ; 
 int /*<<< orphan*/  nb8800_writeb (struct nb8800_priv*,scalar_t__,int) ; 
 struct nb8800_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  readb_poll_timeout_atomic (scalar_t__,int,int,int,int) ; 

__attribute__((used)) static void nb8800_mc_init(struct net_device *dev, int val)
{
	struct nb8800_priv *priv = netdev_priv(dev);

	nb8800_writeb(priv, NB8800_MC_INIT, val);
	readb_poll_timeout_atomic(priv->base + NB8800_MC_INIT, val, !val,
				  1, 1000);
}