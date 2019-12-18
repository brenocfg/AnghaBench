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
typedef  int /*<<< orphan*/  u32 ;
struct fc_lport {int /*<<< orphan*/  port_id; int /*<<< orphan*/  lp_mutex; } ;
struct fc_frame_header {scalar_t__ fh_parm_offset; scalar_t__ fh_df_ctl; scalar_t__ fh_cs_ctl; int /*<<< orphan*/  fh_f_ctl; int /*<<< orphan*/  fh_type; int /*<<< orphan*/  fh_s_id; int /*<<< orphan*/  fh_d_id; int /*<<< orphan*/  fh_r_ctl; } ;
struct fc_frame {int dummy; } ;
struct fc_ct_req {int dummy; } ;
struct fc_ct_hdr {int dummy; } ;
struct fc_bsg_info {int /*<<< orphan*/  sg; int /*<<< orphan*/  nents; int /*<<< orphan*/  rsp_code; struct fc_lport* lport; struct bsg_job* job; } ;
struct TYPE_4__ {int /*<<< orphan*/  sg_list; int /*<<< orphan*/  sg_cnt; } ;
struct TYPE_3__ {int payload_len; int /*<<< orphan*/  sg_cnt; int /*<<< orphan*/  sg_list; } ;
struct bsg_job {TYPE_2__ reply_payload; TYPE_1__ request_payload; } ;

/* Variables and functions */
 int ECOMM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FC_FCTL_REQ ; 
 int /*<<< orphan*/  FC_FS_ACC ; 
 int /*<<< orphan*/  FC_RCTL_DD_UNSOL_CTL ; 
 int /*<<< orphan*/  FC_TYPE_CT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  fc_exch_seq_send (struct fc_lport*,struct fc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct fc_bsg_info*,int /*<<< orphan*/ ) ; 
 struct fc_frame* fc_frame_alloc (struct fc_lport*,int) ; 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 struct fc_frame_header* fc_frame_header_get (struct fc_frame*) ; 
 struct fc_ct_req* fc_frame_payload_get (struct fc_frame*,size_t) ; 
 int /*<<< orphan*/  fc_lport_bsg_resp ; 
 int /*<<< orphan*/  hton24 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct fc_bsg_info*) ; 
 struct fc_bsg_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fc_ct_req*,size_t) ; 

__attribute__((used)) static int fc_lport_ct_request(struct bsg_job *job,
			       struct fc_lport *lport, u32 did, u32 tov)
{
	struct fc_bsg_info *info;
	struct fc_frame *fp;
	struct fc_frame_header *fh;
	struct fc_ct_req *ct;
	size_t len;

	lockdep_assert_held(&lport->lp_mutex);

	fp = fc_frame_alloc(lport, sizeof(struct fc_ct_hdr) +
			    job->request_payload.payload_len);
	if (!fp)
		return -ENOMEM;

	len = job->request_payload.payload_len;
	ct = fc_frame_payload_get(fp, len);

	sg_copy_to_buffer(job->request_payload.sg_list,
			  job->request_payload.sg_cnt,
			  ct, len);

	fh = fc_frame_header_get(fp);
	fh->fh_r_ctl = FC_RCTL_DD_UNSOL_CTL;
	hton24(fh->fh_d_id, did);
	hton24(fh->fh_s_id, lport->port_id);
	fh->fh_type = FC_TYPE_CT;
	hton24(fh->fh_f_ctl, FC_FCTL_REQ);
	fh->fh_cs_ctl = 0;
	fh->fh_df_ctl = 0;
	fh->fh_parm_offset = 0;

	info = kzalloc(sizeof(struct fc_bsg_info), GFP_KERNEL);
	if (!info) {
		fc_frame_free(fp);
		return -ENOMEM;
	}

	info->job = job;
	info->lport = lport;
	info->rsp_code = FC_FS_ACC;
	info->nents = job->reply_payload.sg_cnt;
	info->sg = job->reply_payload.sg_list;

	if (!fc_exch_seq_send(lport, fp, fc_lport_bsg_resp,
			      NULL, info, tov)) {
		kfree(info);
		return -ECOMM;
	}
	return 0;
}