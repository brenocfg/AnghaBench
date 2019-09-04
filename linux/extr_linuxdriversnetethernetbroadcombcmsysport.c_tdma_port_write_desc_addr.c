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
struct dma_desc {int /*<<< orphan*/  addr_lo; int /*<<< orphan*/  addr_status_len; } ;
struct bcm_sysport_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TDMA_WRITE_PORT_HI (unsigned int) ; 
 int /*<<< orphan*/  TDMA_WRITE_PORT_LO (unsigned int) ; 
 int /*<<< orphan*/  tdma_writel (struct bcm_sysport_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void tdma_port_write_desc_addr(struct bcm_sysport_priv *priv,
					     struct dma_desc *desc,
					     unsigned int port)
{
	/* Ports are latched, so write upper address first */
	tdma_writel(priv, desc->addr_status_len, TDMA_WRITE_PORT_HI(port));
	tdma_writel(priv, desc->addr_lo, TDMA_WRITE_PORT_LO(port));
}