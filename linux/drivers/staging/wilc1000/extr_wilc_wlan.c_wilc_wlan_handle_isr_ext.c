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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct wilc {int rx_buffer_offset; TYPE_1__* hif_func; int /*<<< orphan*/ * rx_buffer; } ;
struct rxq_entry_t {int buffer_size; int /*<<< orphan*/ * buffer; } ;
struct TYPE_2__ {int (* hif_block_rx_ext ) (struct wilc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* hif_clear_int_ext ) (struct wilc*,int) ;int /*<<< orphan*/  (* hif_read_size ) (struct wilc*,int*) ;} ;

/* Variables and functions */
 int DATA_INT_CLR ; 
 int ENABLE_RX_VMM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int WILC_RX_BUFF_SIZE ; 
 struct rxq_entry_t* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct wilc*,int*) ; 
 int /*<<< orphan*/  stub2 (struct wilc*,int) ; 
 int stub3 (struct wilc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wilc_wlan_handle_rxq (struct wilc*) ; 
 int /*<<< orphan*/  wilc_wlan_rxq_add (struct wilc*,struct rxq_entry_t*) ; 

__attribute__((used)) static void wilc_wlan_handle_isr_ext(struct wilc *wilc, u32 int_status)
{
	u32 offset = wilc->rx_buffer_offset;
	u8 *buffer = NULL;
	u32 size;
	u32 retries = 0;
	int ret = 0;
	struct rxq_entry_t *rqe;

	size = (int_status & 0x7fff) << 2;

	while (!size && retries < 10) {
		wilc->hif_func->hif_read_size(wilc, &size);
		size = (size & 0x7fff) << 2;
		retries++;
	}

	if (size <= 0)
		return;

	if (WILC_RX_BUFF_SIZE - offset < size)
		offset = 0;

	buffer = &wilc->rx_buffer[offset];

	wilc->hif_func->hif_clear_int_ext(wilc, DATA_INT_CLR | ENABLE_RX_VMM);
	ret = wilc->hif_func->hif_block_rx_ext(wilc, 0, buffer, size);
	if (!ret)
		return;

	offset += size;
	wilc->rx_buffer_offset = offset;
	rqe = kmalloc(sizeof(*rqe), GFP_KERNEL);
	if (!rqe)
		return;

	rqe->buffer = buffer;
	rqe->buffer_size = size;
	wilc_wlan_rxq_add(wilc, rqe);
	wilc_wlan_handle_rxq(wilc);
}