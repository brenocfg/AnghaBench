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
typedef  scalar_t__ u32 ;
struct pt3_board {scalar_t__* regs; } ;
struct TYPE_3__ {struct pt3_board* priv; } ;
struct pt3_adapter {TYPE_2__* desc_buf; int /*<<< orphan*/  adap_idx; TYPE_1__ dvb_adap; } ;
struct TYPE_4__ {int /*<<< orphan*/  b_addr; } ;

/* Variables and functions */
 scalar_t__ OFST_DMA_CTL ; 
 scalar_t__ OFST_DMA_DESC_H ; 
 scalar_t__ OFST_DMA_DESC_L ; 
 scalar_t__ get_dma_base (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

int pt3_start_dma(struct pt3_adapter *adap)
{
	struct pt3_board *pt3 = adap->dvb_adap.priv;
	u32 base = get_dma_base(adap->adap_idx);

	iowrite32(0x02, pt3->regs[0] + base + OFST_DMA_CTL);
	iowrite32(lower_32_bits(adap->desc_buf[0].b_addr),
			pt3->regs[0] + base + OFST_DMA_DESC_L);
	iowrite32(upper_32_bits(adap->desc_buf[0].b_addr),
			pt3->regs[0] + base + OFST_DMA_DESC_H);
	iowrite32(0x01, pt3->regs[0] + base + OFST_DMA_CTL);
	return 0;
}