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
struct mtip_port {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ PORT_IRQ_MASK ; 
 int /*<<< orphan*/  mtip_enable_engine (struct mtip_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtip_enable_fis (struct mtip_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void mtip_deinit_port(struct mtip_port *port)
{
	/* Disable interrupts on this port */
	writel(0, port->mmio + PORT_IRQ_MASK);

	/* Disable the DMA engine */
	mtip_enable_engine(port, 0);

	/* Disable FIS reception */
	mtip_enable_fis(port, 0);
}