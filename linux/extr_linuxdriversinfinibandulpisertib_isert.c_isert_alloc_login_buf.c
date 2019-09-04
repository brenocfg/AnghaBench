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
struct isert_conn {void* login_req_buf; void* login_req_dma; void* login_rsp_buf; void* login_rsp_dma; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ISER_RX_PAYLOAD_SIZE ; 
 void* ib_dma_map_single (struct ib_device*,void*,int,int /*<<< orphan*/ ) ; 
 int ib_dma_mapping_error (struct ib_device*,void*) ; 
 int /*<<< orphan*/  ib_dma_unmap_single (struct ib_device*,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isert_err (char*,int) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
isert_alloc_login_buf(struct isert_conn *isert_conn,
		      struct ib_device *ib_dev)
{
	int ret;

	isert_conn->login_req_buf = kzalloc(sizeof(*isert_conn->login_req_buf),
			GFP_KERNEL);
	if (!isert_conn->login_req_buf)
		return -ENOMEM;

	isert_conn->login_req_dma = ib_dma_map_single(ib_dev,
				isert_conn->login_req_buf,
				ISER_RX_PAYLOAD_SIZE, DMA_FROM_DEVICE);
	ret = ib_dma_mapping_error(ib_dev, isert_conn->login_req_dma);
	if (ret) {
		isert_err("login_req_dma mapping error: %d\n", ret);
		isert_conn->login_req_dma = 0;
		goto out_free_login_req_buf;
	}

	isert_conn->login_rsp_buf = kzalloc(ISER_RX_PAYLOAD_SIZE, GFP_KERNEL);
	if (!isert_conn->login_rsp_buf) {
		ret = -ENOMEM;
		goto out_unmap_login_req_buf;
	}

	isert_conn->login_rsp_dma = ib_dma_map_single(ib_dev,
					isert_conn->login_rsp_buf,
					ISER_RX_PAYLOAD_SIZE, DMA_TO_DEVICE);
	ret = ib_dma_mapping_error(ib_dev, isert_conn->login_rsp_dma);
	if (ret) {
		isert_err("login_rsp_dma mapping error: %d\n", ret);
		isert_conn->login_rsp_dma = 0;
		goto out_free_login_rsp_buf;
	}

	return 0;

out_free_login_rsp_buf:
	kfree(isert_conn->login_rsp_buf);
out_unmap_login_req_buf:
	ib_dma_unmap_single(ib_dev, isert_conn->login_req_dma,
			    ISER_RX_PAYLOAD_SIZE, DMA_FROM_DEVICE);
out_free_login_req_buf:
	kfree(isert_conn->login_req_buf);
	return ret;
}