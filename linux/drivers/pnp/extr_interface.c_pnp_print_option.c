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
struct TYPE_2__ {int /*<<< orphan*/  dma; int /*<<< orphan*/  irq; int /*<<< orphan*/  mem; int /*<<< orphan*/  port; } ;
struct pnp_option {int type; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  pnp_info_buffer_t ;

/* Variables and functions */
#define  IORESOURCE_DMA 131 
#define  IORESOURCE_IO 130 
#define  IORESOURCE_IRQ 129 
#define  IORESOURCE_MEM 128 
 int /*<<< orphan*/  pnp_print_dma (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pnp_print_irq (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pnp_print_mem (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pnp_print_port (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pnp_print_option(pnp_info_buffer_t * buffer, char *space,
			     struct pnp_option *option)
{
	switch (option->type) {
	case IORESOURCE_IO:
		pnp_print_port(buffer, space, &option->u.port);
		break;
	case IORESOURCE_MEM:
		pnp_print_mem(buffer, space, &option->u.mem);
		break;
	case IORESOURCE_IRQ:
		pnp_print_irq(buffer, space, &option->u.irq);
		break;
	case IORESOURCE_DMA:
		pnp_print_dma(buffer, space, &option->u.dma);
		break;
	}
}