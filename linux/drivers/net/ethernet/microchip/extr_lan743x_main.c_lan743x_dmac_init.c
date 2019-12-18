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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int flags; } ;
struct lan743x_adapter {TYPE_1__ csr; } ;

/* Variables and functions */
 int DEFAULT_DMA_DESCRIPTOR_SPACING ; 
 int /*<<< orphan*/  DMAC_CFG ; 
 int /*<<< orphan*/  DMAC_CFG_CH_ARB_SEL_RX_HIGH_ ; 
 int /*<<< orphan*/  DMAC_CFG_COAL_EN_ ; 
 int /*<<< orphan*/  DMAC_CFG_MAX_DSPACE_128_ ; 
 int /*<<< orphan*/  DMAC_CFG_MAX_DSPACE_16_ ; 
 int /*<<< orphan*/  DMAC_CFG_MAX_DSPACE_32_ ; 
 int /*<<< orphan*/  DMAC_CFG_MAX_DSPACE_64_ ; 
 int /*<<< orphan*/  DMAC_CFG_MAX_READ_REQ_SET_ (int) ; 
 int /*<<< orphan*/  DMAC_CMD ; 
 int /*<<< orphan*/  DMAC_CMD_SWR_ ; 
 int /*<<< orphan*/  DMAC_COAL_CFG ; 
 int /*<<< orphan*/  DMAC_COAL_CFG_CSR_EXIT_COAL_ ; 
 int /*<<< orphan*/  DMAC_COAL_CFG_FLUSH_INTS_ ; 
 int /*<<< orphan*/  DMAC_COAL_CFG_INT_EXIT_COAL_ ; 
 int /*<<< orphan*/  DMAC_COAL_CFG_RX_THRES_SET_ (int) ; 
 int /*<<< orphan*/  DMAC_COAL_CFG_TIMER_LIMIT_SET_ (int) ; 
 int /*<<< orphan*/  DMAC_COAL_CFG_TIMER_TX_START_ ; 
 int /*<<< orphan*/  DMAC_COAL_CFG_TX_THRES_SET_ (int) ; 
 int /*<<< orphan*/  DMAC_OBFF_CFG ; 
 int /*<<< orphan*/  DMAC_OBFF_RX_THRES_SET_ (int) ; 
 int /*<<< orphan*/  DMAC_OBFF_TX_THRES_SET_ (int) ; 
#define  DMA_DESCRIPTOR_SPACING_128 131 
#define  DMA_DESCRIPTOR_SPACING_16 130 
#define  DMA_DESCRIPTOR_SPACING_32 129 
#define  DMA_DESCRIPTOR_SPACING_64 128 
 int EPERM ; 
 int LAN743X_CSR_FLAG_IS_A0 ; 
 int /*<<< orphan*/  lan743x_csr_wait_for_bit (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  lan743x_csr_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lan743x_dmac_init(struct lan743x_adapter *adapter)
{
	u32 data = 0;

	lan743x_csr_write(adapter, DMAC_CMD, DMAC_CMD_SWR_);
	lan743x_csr_wait_for_bit(adapter, DMAC_CMD, DMAC_CMD_SWR_,
				 0, 1000, 20000, 100);
	switch (DEFAULT_DMA_DESCRIPTOR_SPACING) {
	case DMA_DESCRIPTOR_SPACING_16:
		data = DMAC_CFG_MAX_DSPACE_16_;
		break;
	case DMA_DESCRIPTOR_SPACING_32:
		data = DMAC_CFG_MAX_DSPACE_32_;
		break;
	case DMA_DESCRIPTOR_SPACING_64:
		data = DMAC_CFG_MAX_DSPACE_64_;
		break;
	case DMA_DESCRIPTOR_SPACING_128:
		data = DMAC_CFG_MAX_DSPACE_128_;
		break;
	default:
		return -EPERM;
	}
	if (!(adapter->csr.flags & LAN743X_CSR_FLAG_IS_A0))
		data |= DMAC_CFG_COAL_EN_;
	data |= DMAC_CFG_CH_ARB_SEL_RX_HIGH_;
	data |= DMAC_CFG_MAX_READ_REQ_SET_(6);
	lan743x_csr_write(adapter, DMAC_CFG, data);
	data = DMAC_COAL_CFG_TIMER_LIMIT_SET_(1);
	data |= DMAC_COAL_CFG_TIMER_TX_START_;
	data |= DMAC_COAL_CFG_FLUSH_INTS_;
	data |= DMAC_COAL_CFG_INT_EXIT_COAL_;
	data |= DMAC_COAL_CFG_CSR_EXIT_COAL_;
	data |= DMAC_COAL_CFG_TX_THRES_SET_(0x0A);
	data |= DMAC_COAL_CFG_RX_THRES_SET_(0x0C);
	lan743x_csr_write(adapter, DMAC_COAL_CFG, data);
	data = DMAC_OBFF_TX_THRES_SET_(0x08);
	data |= DMAC_OBFF_RX_THRES_SET_(0x0A);
	lan743x_csr_write(adapter, DMAC_OBFF_CFG, data);
	return 0;
}