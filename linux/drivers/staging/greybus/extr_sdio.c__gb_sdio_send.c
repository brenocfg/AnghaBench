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
typedef  size_t u16 ;
struct scatterlist {int dummy; } ;
struct mmc_data {unsigned int sg_len; int flags; size_t blksz; struct scatterlist* sg; } ;
struct gb_sdio_transfer_response {int /*<<< orphan*/  data_blksz; int /*<<< orphan*/  data_blocks; } ;
struct gb_sdio_transfer_request {int data_flags; int /*<<< orphan*/ * data; void* data_blksz; void* data_blocks; } ;
struct gb_sdio_host {size_t data_max; int /*<<< orphan*/  mmc; int /*<<< orphan*/  connection; } ;
struct gb_operation {TYPE_2__* response; TYPE_1__* request; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_4__ {struct gb_sdio_transfer_response* payload; } ;
struct TYPE_3__ {struct gb_sdio_transfer_request* payload; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GB_SDIO_TYPE_TRANSFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 void* cpu_to_le16 (size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,size_t,size_t) ; 
 struct gb_operation* gb_operation_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_operation_put (struct gb_operation*) ; 
 int gb_operation_request_send_sync (struct gb_operation*) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 size_t sg_pcopy_to_buffer (struct scatterlist*,unsigned int,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _gb_sdio_send(struct gb_sdio_host *host, struct mmc_data *data,
			 size_t len, u16 nblocks, off_t skip)
{
	struct gb_sdio_transfer_request *request;
	struct gb_sdio_transfer_response *response;
	struct gb_operation *operation;
	struct scatterlist *sg = data->sg;
	unsigned int sg_len = data->sg_len;
	size_t copied;
	u16 send_blksz;
	u16 send_blocks;
	int ret;

	WARN_ON(len > host->data_max);

	operation = gb_operation_create(host->connection, GB_SDIO_TYPE_TRANSFER,
					len + sizeof(*request),
					sizeof(*response), GFP_KERNEL);
	if (!operation)
		return -ENOMEM;

	request = operation->request->payload;
	request->data_flags = data->flags >> 8;
	request->data_blocks = cpu_to_le16(nblocks);
	request->data_blksz = cpu_to_le16(data->blksz);

	copied = sg_pcopy_to_buffer(sg, sg_len, &request->data[0], len, skip);

	if (copied != len) {
		ret = -EINVAL;
		goto err_put_operation;
	}

	ret = gb_operation_request_send_sync(operation);
	if (ret < 0)
		goto err_put_operation;

	response = operation->response->payload;

	send_blocks = le16_to_cpu(response->data_blocks);
	send_blksz = le16_to_cpu(response->data_blksz);

	if (len != send_blksz * send_blocks) {
		dev_err(mmc_dev(host->mmc), "send: size received: %zu != %d\n",
			len, send_blksz * send_blocks);
		ret = -EINVAL;
	}

err_put_operation:
	gb_operation_put(operation);

	return ret;
}