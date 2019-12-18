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
struct rtl8169_private {TYPE_1__* RxDescArray; int /*<<< orphan*/ ** Rx_databuff; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 unsigned int NUM_RX_DESC ; 
 int /*<<< orphan*/  R8169_RX_BUF_SIZE ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8169_make_unusable_by_asic (TYPE_1__*) ; 
 int /*<<< orphan*/  tp_to_dev (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl8169_rx_clear(struct rtl8169_private *tp)
{
	unsigned int i;

	for (i = 0; i < NUM_RX_DESC && tp->Rx_databuff[i]; i++) {
		dma_unmap_page(tp_to_dev(tp),
			       le64_to_cpu(tp->RxDescArray[i].addr),
			       R8169_RX_BUF_SIZE, DMA_FROM_DEVICE);
		__free_pages(tp->Rx_databuff[i], get_order(R8169_RX_BUF_SIZE));
		tp->Rx_databuff[i] = NULL;
		rtl8169_make_unusable_by_asic(tp->RxDescArray + i);
	}
}