#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int done; } ;
union cvmx_mio_boot_dma_intx {scalar_t__ u64; TYPE_2__ s; } ;
struct TYPE_3__ {int size; } ;
union cvmx_mio_boot_dma_cfgx {scalar_t__ u64; TYPE_1__ s; } ;
struct octeon_cf_port {int /*<<< orphan*/  c0; scalar_t__ dma_base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_SRST ; 
 scalar_t__ DMA_CFG ; 
 scalar_t__ DMA_INT ; 
 scalar_t__ DMA_INT_EN ; 
 int /*<<< orphan*/  __raw_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (scalar_t__,scalar_t__) ; 
 struct octeon_cf_port* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void octeon_cf_shutdown(struct device *dev)
{
	union cvmx_mio_boot_dma_cfgx dma_cfg;
	union cvmx_mio_boot_dma_intx dma_int;

	struct octeon_cf_port *cf_port = dev_get_platdata(dev);

	if (cf_port->dma_base) {
		/* Stop and clear the dma engine.  */
		dma_cfg.u64 = 0;
		dma_cfg.s.size = -1;
		cvmx_write_csr(cf_port->dma_base + DMA_CFG, dma_cfg.u64);

		/* Disable the interrupt.  */
		dma_int.u64 = 0;
		cvmx_write_csr(cf_port->dma_base + DMA_INT_EN, dma_int.u64);

		/* Clear the DMA complete status */
		dma_int.s.done = 1;
		cvmx_write_csr(cf_port->dma_base + DMA_INT, dma_int.u64);

		__raw_writeb(0, cf_port->c0);
		udelay(20);
		__raw_writeb(ATA_SRST, cf_port->c0);
		udelay(20);
		__raw_writeb(0, cf_port->c0);
		mdelay(100);
	}
}