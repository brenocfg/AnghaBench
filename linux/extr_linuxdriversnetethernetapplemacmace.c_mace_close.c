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
struct mace_data {struct mace* mace; } ;
struct mace {int imr; scalar_t__ maccc; } ;

/* Variables and functions */
 int /*<<< orphan*/  mace_dma_off (struct net_device*) ; 
 struct mace_data* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mace_close(struct net_device *dev)
{
	struct mace_data *mp = netdev_priv(dev);
	volatile struct mace *mb = mp->mace;

	mb->maccc = 0;		/* disable rx and tx	 */
	mb->imr = 0xFF;		/* disable all irqs	 */
	mace_dma_off(dev);	/* disable rx and tx dma */

	return 0;
}