#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct qla_image_version_list {int /*<<< orphan*/  count; struct qla_image_version* version; } ;
struct TYPE_9__ {int /*<<< orphan*/  option; int /*<<< orphan*/  offset; int /*<<< orphan*/  device; } ;
struct qla_image_version {TYPE_2__ field_address; int /*<<< orphan*/  field_info; } ;
struct qla_hw_data {int /*<<< orphan*/  s_dma_pool; } ;
struct TYPE_10__ {scalar_t__* vendor_rsp; } ;
struct TYPE_11__ {TYPE_3__ vendor_reply; } ;
struct fc_bsg_reply {int result; int /*<<< orphan*/  reply_payload_rcv_len; TYPE_4__ reply_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  sg_cnt; int /*<<< orphan*/  sg_list; } ;
struct bsg_job {int reply_len; TYPE_1__ request_payload; struct fc_bsg_reply* reply; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_12__ {struct qla_hw_data* hw; } ;
typedef  TYPE_5__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int /*<<< orphan*/  bsg ;

/* Variables and functions */
 int DID_OK ; 
 int DMA_POOL_SIZE ; 
 scalar_t__ EXT_STATUS_MAILBOX ; 
 scalar_t__ EXT_STATUS_NO_MEMORY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bsg_job_done (struct bsg_job*,int,int /*<<< orphan*/ ) ; 
 void* dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* fc_bsg_to_shost (struct bsg_job*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 int qla2x00_write_sfp (TYPE_5__*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qla_image_version_list*,int) ; 
 TYPE_5__* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static int
qla2x00_update_fru_versions(struct bsg_job *bsg_job)
{
	struct fc_bsg_reply *bsg_reply = bsg_job->reply;
	struct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qla_host_t *vha = shost_priv(host);
	struct qla_hw_data *ha = vha->hw;
	int rval = 0;
	uint8_t bsg[DMA_POOL_SIZE];
	struct qla_image_version_list *list = (void *)bsg;
	struct qla_image_version *image;
	uint32_t count;
	dma_addr_t sfp_dma;
	void *sfp = dma_pool_alloc(ha->s_dma_pool, GFP_KERNEL, &sfp_dma);

	if (!sfp) {
		bsg_reply->reply_data.vendor_reply.vendor_rsp[0] =
		    EXT_STATUS_NO_MEMORY;
		goto done;
	}

	sg_copy_to_buffer(bsg_job->request_payload.sg_list,
	    bsg_job->request_payload.sg_cnt, list, sizeof(bsg));

	image = list->version;
	count = list->count;
	while (count--) {
		memcpy(sfp, &image->field_info, sizeof(image->field_info));
		rval = qla2x00_write_sfp(vha, sfp_dma, sfp,
		    image->field_address.device, image->field_address.offset,
		    sizeof(image->field_info), image->field_address.option);
		if (rval) {
			bsg_reply->reply_data.vendor_reply.vendor_rsp[0] =
			    EXT_STATUS_MAILBOX;
			goto dealloc;
		}
		image++;
	}

	bsg_reply->reply_data.vendor_reply.vendor_rsp[0] = 0;

dealloc:
	dma_pool_free(ha->s_dma_pool, sfp, sfp_dma);

done:
	bsg_job->reply_len = sizeof(struct fc_bsg_reply);
	bsg_reply->result = DID_OK << 16;
	bsg_job_done(bsg_job, bsg_reply->result,
		       bsg_reply->reply_payload_rcv_len);

	return 0;
}