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
struct TYPE_2__ {int /*<<< orphan*/  isr_table_cio; } ;
struct dsi_data {TYPE_1__ isr_tables; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSI_CIO_IRQ_ERROR_MASK ; 
 int /*<<< orphan*/  DSI_COMPLEXIO_IRQ_ENABLE ; 
 int /*<<< orphan*/  DSI_COMPLEXIO_IRQ_STATUS ; 
 int /*<<< orphan*/  _omap_dsi_configure_irqs (struct dsi_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _omap_dsi_set_irqs_cio(struct dsi_data *dsi)
{
	_omap_dsi_configure_irqs(dsi, dsi->isr_tables.isr_table_cio,
			ARRAY_SIZE(dsi->isr_tables.isr_table_cio),
			DSI_CIO_IRQ_ERROR_MASK,
			DSI_COMPLEXIO_IRQ_ENABLE, DSI_COMPLEXIO_IRQ_STATUS);
}