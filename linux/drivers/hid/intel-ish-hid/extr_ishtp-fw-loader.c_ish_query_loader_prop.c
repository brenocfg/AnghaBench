#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_8__ {int xfer_mode; int max_dma_buf_size; int /*<<< orphan*/  max_fw_image_size; } ;
struct TYPE_7__ {int /*<<< orphan*/  value; } ;
struct TYPE_6__ {int /*<<< orphan*/  build; int /*<<< orphan*/  hotfix; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct shim_fw_info {TYPE_4__ ldr_capability; TYPE_3__ ldr_version; int /*<<< orphan*/  protocol_version; TYPE_2__ ish_fw_version; } ;
struct loader_xfer_query_response {struct shim_fw_info fw_info; } ;
struct TYPE_5__ {int /*<<< orphan*/  command; } ;
struct loader_xfer_query {int /*<<< orphan*/  image_size; TYPE_1__ hdr; } ;
struct ishtp_cl_data {int flag_retry; } ;
struct firmware {int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  ldr_xfer_query_resp ;
typedef  int /*<<< orphan*/  ldr_xfer_query ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOSPC ; 
 int L1_CACHE_BYTES ; 
 int /*<<< orphan*/  LOADER_CMD_XFER_QUERY ; 
 int LOADER_XFER_MODE_DIRECT_DMA ; 
 int /*<<< orphan*/  cl_data_to_dev (struct ishtp_cl_data*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dma_buf_size_limit ; 
 int loader_cl_send (struct ishtp_cl_data*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct loader_xfer_query*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ish_query_loader_prop(struct ishtp_cl_data *client_data,
				 const struct firmware *fw,
				 struct shim_fw_info *fw_info)
{
	int rv;
	struct loader_xfer_query ldr_xfer_query;
	struct loader_xfer_query_response ldr_xfer_query_resp;

	memset(&ldr_xfer_query, 0, sizeof(ldr_xfer_query));
	ldr_xfer_query.hdr.command = LOADER_CMD_XFER_QUERY;
	ldr_xfer_query.image_size = fw->size;
	rv = loader_cl_send(client_data,
			    (u8 *)&ldr_xfer_query,
			    sizeof(ldr_xfer_query),
			    (u8 *)&ldr_xfer_query_resp,
			    sizeof(ldr_xfer_query_resp));
	if (rv < 0) {
		client_data->flag_retry = true;
		return rv;
	}

	/* On success, the return value is the received buffer size */
	if (rv != sizeof(struct loader_xfer_query_response)) {
		dev_err(cl_data_to_dev(client_data),
			"data size %d is not equal to size of loader_xfer_query_response %zu\n",
			rv, sizeof(struct loader_xfer_query_response));
		client_data->flag_retry = true;
		return -EMSGSIZE;
	}

	/* Save fw_info for use outside this function */
	*fw_info = ldr_xfer_query_resp.fw_info;

	/* Loader firmware properties */
	dev_dbg(cl_data_to_dev(client_data),
		"ish_fw_version: major=%d minor=%d hotfix=%d build=%d protocol_version=0x%x loader_version=%d\n",
		fw_info->ish_fw_version.major,
		fw_info->ish_fw_version.minor,
		fw_info->ish_fw_version.hotfix,
		fw_info->ish_fw_version.build,
		fw_info->protocol_version,
		fw_info->ldr_version.value);

	dev_dbg(cl_data_to_dev(client_data),
		"loader_capability: max_fw_image_size=0x%x xfer_mode=%d max_dma_buf_size=0x%x dma_buf_size_limit=0x%x\n",
		fw_info->ldr_capability.max_fw_image_size,
		fw_info->ldr_capability.xfer_mode,
		fw_info->ldr_capability.max_dma_buf_size,
		dma_buf_size_limit);

	/* Sanity checks */
	if (fw_info->ldr_capability.max_fw_image_size < fw->size) {
		dev_err(cl_data_to_dev(client_data),
			"ISH firmware size %zu is greater than Shim firmware loader max supported %d\n",
			fw->size,
			fw_info->ldr_capability.max_fw_image_size);
		return -ENOSPC;
	}

	/* For DMA the buffer size should be multiple of cacheline size */
	if ((fw_info->ldr_capability.xfer_mode & LOADER_XFER_MODE_DIRECT_DMA) &&
	    (fw_info->ldr_capability.max_dma_buf_size % L1_CACHE_BYTES)) {
		dev_err(cl_data_to_dev(client_data),
			"Shim firmware loader buffer size %d should be multiple of cacheline\n",
			fw_info->ldr_capability.max_dma_buf_size);
		return -EINVAL;
	}

	return 0;
}