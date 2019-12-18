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
struct pnp_dev {int dummy; } ;

/* Variables and functions */
 int pnp_dma (struct pnp_dev*,int /*<<< orphan*/ ) ; 
 int pnp_irq (struct pnp_dev*,int /*<<< orphan*/ ) ; 
 int pnp_mem_len (struct pnp_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnp_mem_start (struct pnp_dev*,int /*<<< orphan*/ ) ; 
 int pnp_port_len (struct pnp_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnp_port_start (struct pnp_dev*,int /*<<< orphan*/ ) ; 

int pnp_is_active(struct pnp_dev *dev)
{
	/*
	 * I don't think this is very reliable because pnp_disable_dev()
	 * only clears out auto-assigned resources.
	 */
	if (!pnp_port_start(dev, 0) && pnp_port_len(dev, 0) <= 1 &&
	    !pnp_mem_start(dev, 0) && pnp_mem_len(dev, 0) <= 1 &&
	    pnp_irq(dev, 0) == -1 && pnp_dma(dev, 0) == -1)
		return 0;
	else
		return 1;
}