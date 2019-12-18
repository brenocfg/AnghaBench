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
struct isert_device {struct ib_device* ib_device; } ;
struct isert_conn {struct isert_device* device; } ;
struct isert_cmd {int dummy; } ;
struct iser_tx_desc {int /*<<< orphan*/  dma_addr; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ISER_HEADERS_LEN ; 
 int /*<<< orphan*/  __isert_create_send_desc (struct isert_device*,struct iser_tx_desc*) ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_cpu (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
isert_create_send_desc(struct isert_conn *isert_conn,
		       struct isert_cmd *isert_cmd,
		       struct iser_tx_desc *tx_desc)
{
	struct isert_device *device = isert_conn->device;
	struct ib_device *ib_dev = device->ib_device;

	ib_dma_sync_single_for_cpu(ib_dev, tx_desc->dma_addr,
				   ISER_HEADERS_LEN, DMA_TO_DEVICE);

	__isert_create_send_desc(device, tx_desc);
}