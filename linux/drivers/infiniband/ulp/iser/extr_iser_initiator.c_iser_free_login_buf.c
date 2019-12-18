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
struct iser_login_desc {int /*<<< orphan*/ * rsp; int /*<<< orphan*/ * req; int /*<<< orphan*/  rsp_dma; int /*<<< orphan*/  req_dma; } ;
struct iser_device {int /*<<< orphan*/  ib_device; } ;
struct TYPE_2__ {struct iser_device* device; } ;
struct iser_conn {struct iser_login_desc login_desc; TYPE_1__ ib_conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ISCSI_DEF_MAX_RECV_SEG_LEN ; 
 int /*<<< orphan*/  ISER_RX_LOGIN_SIZE ; 
 int /*<<< orphan*/  ib_dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iser_free_login_buf(struct iser_conn *iser_conn)
{
	struct iser_device *device = iser_conn->ib_conn.device;
	struct iser_login_desc *desc = &iser_conn->login_desc;

	if (!desc->req)
		return;

	ib_dma_unmap_single(device->ib_device, desc->req_dma,
			    ISCSI_DEF_MAX_RECV_SEG_LEN, DMA_TO_DEVICE);

	ib_dma_unmap_single(device->ib_device, desc->rsp_dma,
			    ISER_RX_LOGIN_SIZE, DMA_FROM_DEVICE);

	kfree(desc->req);
	kfree(desc->rsp);

	/* make sure we never redo any unmapping */
	desc->req = NULL;
	desc->rsp = NULL;
}