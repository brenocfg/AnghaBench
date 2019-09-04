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
struct iser_login_desc {void* req; void* req_dma; void* rsp; void* rsp_dma; } ;
struct iser_device {int /*<<< orphan*/  ib_device; } ;
struct TYPE_2__ {struct iser_device* device; } ;
struct iser_conn {struct iser_login_desc login_desc; TYPE_1__ ib_conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ISCSI_DEF_MAX_RECV_SEG_LEN ; 
 int /*<<< orphan*/  ISER_RX_LOGIN_SIZE ; 
 void* ib_dma_map_single (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ib_dma_mapping_error (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ib_dma_unmap_single (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iser_alloc_login_buf(struct iser_conn *iser_conn)
{
	struct iser_device *device = iser_conn->ib_conn.device;
	struct iser_login_desc *desc = &iser_conn->login_desc;

	desc->req = kmalloc(ISCSI_DEF_MAX_RECV_SEG_LEN, GFP_KERNEL);
	if (!desc->req)
		return -ENOMEM;

	desc->req_dma = ib_dma_map_single(device->ib_device, desc->req,
					  ISCSI_DEF_MAX_RECV_SEG_LEN,
					  DMA_TO_DEVICE);
	if (ib_dma_mapping_error(device->ib_device,
				desc->req_dma))
		goto free_req;

	desc->rsp = kmalloc(ISER_RX_LOGIN_SIZE, GFP_KERNEL);
	if (!desc->rsp)
		goto unmap_req;

	desc->rsp_dma = ib_dma_map_single(device->ib_device, desc->rsp,
					   ISER_RX_LOGIN_SIZE,
					   DMA_FROM_DEVICE);
	if (ib_dma_mapping_error(device->ib_device,
				desc->rsp_dma))
		goto free_rsp;

	return 0;

free_rsp:
	kfree(desc->rsp);
unmap_req:
	ib_dma_unmap_single(device->ib_device, desc->req_dma,
			    ISCSI_DEF_MAX_RECV_SEG_LEN,
			    DMA_TO_DEVICE);
free_req:
	kfree(desc->req);

	return -ENOMEM;
}