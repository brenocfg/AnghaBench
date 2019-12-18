#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {TYPE_4__* rx; TYPE_2__* tx; } ;
struct queue_entry_priv_mmio {int desc_dma; } ;
struct TYPE_8__ {int limit; int desc_size; TYPE_3__* entries; } ;
struct TYPE_7__ {struct queue_entry_priv_mmio* priv_data; } ;
struct TYPE_6__ {int limit; int desc_size; TYPE_1__* entries; } ;
struct TYPE_5__ {struct queue_entry_priv_mmio* priv_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC0_BASE_CSR ; 
 int /*<<< orphan*/  AC0_BASE_CSR_RING_REGISTER ; 
 int /*<<< orphan*/  AC1_BASE_CSR ; 
 int /*<<< orphan*/  AC1_BASE_CSR_RING_REGISTER ; 
 int /*<<< orphan*/  AC2_BASE_CSR ; 
 int /*<<< orphan*/  AC2_BASE_CSR_RING_REGISTER ; 
 int /*<<< orphan*/  AC3_BASE_CSR ; 
 int /*<<< orphan*/  AC3_BASE_CSR_RING_REGISTER ; 
 int /*<<< orphan*/  LOAD_TX_RING_CSR ; 
 int /*<<< orphan*/  LOAD_TX_RING_CSR_LOAD_TXD_AC0 ; 
 int /*<<< orphan*/  LOAD_TX_RING_CSR_LOAD_TXD_AC1 ; 
 int /*<<< orphan*/  LOAD_TX_RING_CSR_LOAD_TXD_AC2 ; 
 int /*<<< orphan*/  LOAD_TX_RING_CSR_LOAD_TXD_AC3 ; 
 int /*<<< orphan*/  RX_BASE_CSR ; 
 int /*<<< orphan*/  RX_BASE_CSR_RING_REGISTER ; 
 int /*<<< orphan*/  RX_CNTL_CSR ; 
 int /*<<< orphan*/  RX_CNTL_CSR_LOAD_RXD ; 
 int /*<<< orphan*/  RX_RING_CSR ; 
 int /*<<< orphan*/  RX_RING_CSR_RING_SIZE ; 
 int /*<<< orphan*/  RX_RING_CSR_RXD_SIZE ; 
 int /*<<< orphan*/  RX_RING_CSR_RXD_WRITEBACK_SIZE ; 
 int /*<<< orphan*/  TX_DMA_DST_CSR ; 
 int /*<<< orphan*/  TX_DMA_DST_CSR_DEST_AC0 ; 
 int /*<<< orphan*/  TX_DMA_DST_CSR_DEST_AC1 ; 
 int /*<<< orphan*/  TX_DMA_DST_CSR_DEST_AC2 ; 
 int /*<<< orphan*/  TX_DMA_DST_CSR_DEST_AC3 ; 
 int /*<<< orphan*/  TX_RING_CSR0 ; 
 int /*<<< orphan*/  TX_RING_CSR0_AC0_RING_SIZE ; 
 int /*<<< orphan*/  TX_RING_CSR0_AC1_RING_SIZE ; 
 int /*<<< orphan*/  TX_RING_CSR0_AC2_RING_SIZE ; 
 int /*<<< orphan*/  TX_RING_CSR0_AC3_RING_SIZE ; 
 int /*<<< orphan*/  TX_RING_CSR1 ; 
 int /*<<< orphan*/  TX_RING_CSR1_TXD_SIZE ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt61pci_init_queues(struct rt2x00_dev *rt2x00dev)
{
	struct queue_entry_priv_mmio *entry_priv;
	u32 reg;

	/*
	 * Initialize registers.
	 */
	reg = rt2x00mmio_register_read(rt2x00dev, TX_RING_CSR0);
	rt2x00_set_field32(&reg, TX_RING_CSR0_AC0_RING_SIZE,
			   rt2x00dev->tx[0].limit);
	rt2x00_set_field32(&reg, TX_RING_CSR0_AC1_RING_SIZE,
			   rt2x00dev->tx[1].limit);
	rt2x00_set_field32(&reg, TX_RING_CSR0_AC2_RING_SIZE,
			   rt2x00dev->tx[2].limit);
	rt2x00_set_field32(&reg, TX_RING_CSR0_AC3_RING_SIZE,
			   rt2x00dev->tx[3].limit);
	rt2x00mmio_register_write(rt2x00dev, TX_RING_CSR0, reg);

	reg = rt2x00mmio_register_read(rt2x00dev, TX_RING_CSR1);
	rt2x00_set_field32(&reg, TX_RING_CSR1_TXD_SIZE,
			   rt2x00dev->tx[0].desc_size / 4);
	rt2x00mmio_register_write(rt2x00dev, TX_RING_CSR1, reg);

	entry_priv = rt2x00dev->tx[0].entries[0].priv_data;
	reg = rt2x00mmio_register_read(rt2x00dev, AC0_BASE_CSR);
	rt2x00_set_field32(&reg, AC0_BASE_CSR_RING_REGISTER,
			   entry_priv->desc_dma);
	rt2x00mmio_register_write(rt2x00dev, AC0_BASE_CSR, reg);

	entry_priv = rt2x00dev->tx[1].entries[0].priv_data;
	reg = rt2x00mmio_register_read(rt2x00dev, AC1_BASE_CSR);
	rt2x00_set_field32(&reg, AC1_BASE_CSR_RING_REGISTER,
			   entry_priv->desc_dma);
	rt2x00mmio_register_write(rt2x00dev, AC1_BASE_CSR, reg);

	entry_priv = rt2x00dev->tx[2].entries[0].priv_data;
	reg = rt2x00mmio_register_read(rt2x00dev, AC2_BASE_CSR);
	rt2x00_set_field32(&reg, AC2_BASE_CSR_RING_REGISTER,
			   entry_priv->desc_dma);
	rt2x00mmio_register_write(rt2x00dev, AC2_BASE_CSR, reg);

	entry_priv = rt2x00dev->tx[3].entries[0].priv_data;
	reg = rt2x00mmio_register_read(rt2x00dev, AC3_BASE_CSR);
	rt2x00_set_field32(&reg, AC3_BASE_CSR_RING_REGISTER,
			   entry_priv->desc_dma);
	rt2x00mmio_register_write(rt2x00dev, AC3_BASE_CSR, reg);

	reg = rt2x00mmio_register_read(rt2x00dev, RX_RING_CSR);
	rt2x00_set_field32(&reg, RX_RING_CSR_RING_SIZE, rt2x00dev->rx->limit);
	rt2x00_set_field32(&reg, RX_RING_CSR_RXD_SIZE,
			   rt2x00dev->rx->desc_size / 4);
	rt2x00_set_field32(&reg, RX_RING_CSR_RXD_WRITEBACK_SIZE, 4);
	rt2x00mmio_register_write(rt2x00dev, RX_RING_CSR, reg);

	entry_priv = rt2x00dev->rx->entries[0].priv_data;
	reg = rt2x00mmio_register_read(rt2x00dev, RX_BASE_CSR);
	rt2x00_set_field32(&reg, RX_BASE_CSR_RING_REGISTER,
			   entry_priv->desc_dma);
	rt2x00mmio_register_write(rt2x00dev, RX_BASE_CSR, reg);

	reg = rt2x00mmio_register_read(rt2x00dev, TX_DMA_DST_CSR);
	rt2x00_set_field32(&reg, TX_DMA_DST_CSR_DEST_AC0, 2);
	rt2x00_set_field32(&reg, TX_DMA_DST_CSR_DEST_AC1, 2);
	rt2x00_set_field32(&reg, TX_DMA_DST_CSR_DEST_AC2, 2);
	rt2x00_set_field32(&reg, TX_DMA_DST_CSR_DEST_AC3, 2);
	rt2x00mmio_register_write(rt2x00dev, TX_DMA_DST_CSR, reg);

	reg = rt2x00mmio_register_read(rt2x00dev, LOAD_TX_RING_CSR);
	rt2x00_set_field32(&reg, LOAD_TX_RING_CSR_LOAD_TXD_AC0, 1);
	rt2x00_set_field32(&reg, LOAD_TX_RING_CSR_LOAD_TXD_AC1, 1);
	rt2x00_set_field32(&reg, LOAD_TX_RING_CSR_LOAD_TXD_AC2, 1);
	rt2x00_set_field32(&reg, LOAD_TX_RING_CSR_LOAD_TXD_AC3, 1);
	rt2x00mmio_register_write(rt2x00dev, LOAD_TX_RING_CSR, reg);

	reg = rt2x00mmio_register_read(rt2x00dev, RX_CNTL_CSR);
	rt2x00_set_field32(&reg, RX_CNTL_CSR_LOAD_RXD, 1);
	rt2x00mmio_register_write(rt2x00dev, RX_CNTL_CSR, reg);

	return 0;
}