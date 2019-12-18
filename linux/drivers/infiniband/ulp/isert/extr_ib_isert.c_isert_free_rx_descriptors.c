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
struct isert_conn {struct iser_rx_desc* rx_descs; TYPE_1__* device; } ;
struct iser_rx_desc {int /*<<< orphan*/  dma_addr; } ;
struct ib_device {int dummy; } ;
struct TYPE_2__ {struct ib_device* ib_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ISERT_QP_MAX_RECV_DTOS ; 
 int /*<<< orphan*/  ISER_RX_PAYLOAD_SIZE ; 
 int /*<<< orphan*/  ib_dma_unmap_single (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct iser_rx_desc*) ; 

__attribute__((used)) static void
isert_free_rx_descriptors(struct isert_conn *isert_conn)
{
	struct ib_device *ib_dev = isert_conn->device->ib_device;
	struct iser_rx_desc *rx_desc;
	int i;

	if (!isert_conn->rx_descs)
		return;

	rx_desc = isert_conn->rx_descs;
	for (i = 0; i < ISERT_QP_MAX_RECV_DTOS; i++, rx_desc++)  {
		ib_dma_unmap_single(ib_dev, rx_desc->dma_addr,
				    ISER_RX_PAYLOAD_SIZE, DMA_FROM_DEVICE);
	}

	kfree(isert_conn->rx_descs);
	isert_conn->rx_descs = NULL;
}