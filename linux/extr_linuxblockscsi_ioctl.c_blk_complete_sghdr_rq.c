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
struct sg_io_hdr {int status; int sb_len_wr; scalar_t__ sbp; scalar_t__ mx_sb_len; int /*<<< orphan*/  resid; int /*<<< orphan*/  info; int /*<<< orphan*/  driver_status; int /*<<< orphan*/  host_status; int /*<<< orphan*/  masked_status; int /*<<< orphan*/  msg_status; } ;
struct scsi_request {int result; int /*<<< orphan*/  sense; scalar_t__ sense_len; int /*<<< orphan*/  resid_len; } ;
struct request {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  SG_INFO_CHECK ; 
 int blk_rq_unmap_user (struct bio*) ; 
 int /*<<< orphan*/  copy_to_user (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  driver_byte (int) ; 
 int /*<<< orphan*/  host_byte (int) ; 
 int min (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  msg_byte (int) ; 
 struct scsi_request* scsi_req (struct request*) ; 
 int /*<<< orphan*/  status_byte (int) ; 

__attribute__((used)) static int blk_complete_sghdr_rq(struct request *rq, struct sg_io_hdr *hdr,
				 struct bio *bio)
{
	struct scsi_request *req = scsi_req(rq);
	int r, ret = 0;

	/*
	 * fill in all the output members
	 */
	hdr->status = req->result & 0xff;
	hdr->masked_status = status_byte(req->result);
	hdr->msg_status = msg_byte(req->result);
	hdr->host_status = host_byte(req->result);
	hdr->driver_status = driver_byte(req->result);
	hdr->info = 0;
	if (hdr->masked_status || hdr->host_status || hdr->driver_status)
		hdr->info |= SG_INFO_CHECK;
	hdr->resid = req->resid_len;
	hdr->sb_len_wr = 0;

	if (req->sense_len && hdr->sbp) {
		int len = min((unsigned int) hdr->mx_sb_len, req->sense_len);

		if (!copy_to_user(hdr->sbp, req->sense, len))
			hdr->sb_len_wr = len;
		else
			ret = -EFAULT;
	}

	r = blk_rq_unmap_user(bio);
	if (!ret)
		ret = r;

	return ret;
}