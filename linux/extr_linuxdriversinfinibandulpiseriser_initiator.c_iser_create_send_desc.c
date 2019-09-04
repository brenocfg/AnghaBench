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
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct iser_tx_desc {int num_sge; TYPE_2__ iser_header; int /*<<< orphan*/  dma_addr; } ;
struct iser_device {int /*<<< orphan*/  ib_device; } ;
struct iser_ctrl {int dummy; } ;
struct TYPE_3__ {struct iser_device* device; } ;
struct iser_conn {TYPE_1__ ib_conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ISER_HEADERS_LEN ; 
 int /*<<< orphan*/  ISER_VER ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void iser_create_send_desc(struct iser_conn	*iser_conn,
				  struct iser_tx_desc	*tx_desc)
{
	struct iser_device *device = iser_conn->ib_conn.device;

	ib_dma_sync_single_for_cpu(device->ib_device,
		tx_desc->dma_addr, ISER_HEADERS_LEN, DMA_TO_DEVICE);

	memset(&tx_desc->iser_header, 0, sizeof(struct iser_ctrl));
	tx_desc->iser_header.flags = ISER_VER;
	tx_desc->num_sge = 1;
}