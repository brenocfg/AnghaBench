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
typedef  scalar_t__ u8 ;
typedef  int u64 ;
struct sg_mapping_iter {size_t consumed; size_t length; scalar_t__ addr; } ;
struct mmc_request {TYPE_1__* data; } ;
struct cvm_mmc_host {scalar_t__ base; struct sg_mapping_iter smi; } ;
struct TYPE_2__ {unsigned int blocks; unsigned int blksz; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;

/* Variables and functions */
 scalar_t__ MIO_EMM_BUF_DAT (struct cvm_mmc_host*) ; 
 scalar_t__ MIO_EMM_BUF_IDX (struct cvm_mmc_host*) ; 
 int /*<<< orphan*/  SG_MITER_FROM_SG ; 
 int /*<<< orphan*/  sg_miter_next (struct sg_mapping_iter*) ; 
 int /*<<< orphan*/  sg_miter_start (struct sg_mapping_iter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_miter_stop (struct sg_mapping_iter*) ; 
 int /*<<< orphan*/  writeq (int,scalar_t__) ; 

__attribute__((used)) static void do_write_request(struct cvm_mmc_host *host, struct mmc_request *mrq)
{
	unsigned int data_len = mrq->data->blocks * mrq->data->blksz;
	struct sg_mapping_iter *smi = &host->smi;
	unsigned int bytes_xfered;
	int shift = 56;
	u64 dat = 0;

	/* Copy data to the xmit buffer before issuing the command. */
	sg_miter_start(smi, mrq->data->sg, mrq->data->sg_len, SG_MITER_FROM_SG);

	/* Auto inc from offset zero, dbuf zero */
	writeq(0x10000ull, host->base + MIO_EMM_BUF_IDX(host));

	for (bytes_xfered = 0; bytes_xfered < data_len;) {
		if (smi->consumed >= smi->length) {
			if (!sg_miter_next(smi))
				break;
			smi->consumed = 0;
		}

		while (smi->consumed < smi->length && shift >= 0) {
			dat |= (u64)((u8 *)smi->addr)[smi->consumed] << shift;
			bytes_xfered++;
			smi->consumed++;
			shift -= 8;
		}

		if (shift < 0) {
			writeq(dat, host->base + MIO_EMM_BUF_DAT(host));
			shift = 56;
			dat = 0;
		}
	}
	sg_miter_stop(smi);
}