#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
struct srp_login_rsp {int /*<<< orphan*/  buf_fmt; void* max_ti_iu_len; void* max_it_iu_len; int /*<<< orphan*/  tag; void* req_lim_delta; int /*<<< orphan*/  opcode; } ;
struct TYPE_11__ {TYPE_4__* window; } ;
struct scsi_info {int /*<<< orphan*/  dev; TYPE_5__ dds; scalar_t__ credit; int /*<<< orphan*/  request_limit; } ;
struct iu_entry {int /*<<< orphan*/  remote_token; TYPE_3__* sbuf; } ;
struct TYPE_8__ {int len; int /*<<< orphan*/  tag; } ;
struct ibmvscsis_cmd {TYPE_2__ rsp; struct iu_entry* iue; } ;
struct format_code {int /*<<< orphan*/  buffers; } ;
struct TYPE_7__ {struct srp_login_rsp login_rsp; } ;
struct TYPE_12__ {TYPE_1__ srp; } ;
struct TYPE_10__ {int /*<<< orphan*/  liobn; } ;
struct TYPE_9__ {int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 long ADAPT_SUCCESS ; 
 int CLIENT_FAILED ; 
 int /*<<< orphan*/  ERR_DISCONNECT_RECONNECT ; 
#define  H_DEST_PARM 131 
#define  H_PERMISSION 130 
#define  H_SOURCE_PARM 129 
#define  H_SUCCESS 128 
 size_t LOCAL ; 
 size_t REMOTE ; 
 int RESPONSE_Q_DOWN ; 
 int /*<<< orphan*/  SRP_LOGIN_RSP ; 
 int /*<<< orphan*/  SRP_MAX_IU_LEN ; 
 int /*<<< orphan*/  SUPPORTED_FORMATS ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  connection_broken (struct scsi_info*) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,long) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 long h_copy_rdma (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvscsis_post_disconnect (struct scsi_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct srp_login_rsp*,int /*<<< orphan*/ ,int) ; 
 TYPE_6__* vio_iu (struct iu_entry*) ; 

__attribute__((used)) static long ibmvscsis_login_rsp(struct scsi_info *vscsi,
				struct ibmvscsis_cmd *cmd)
{
	struct iu_entry *iue = cmd->iue;
	struct srp_login_rsp *rsp = &vio_iu(iue)->srp.login_rsp;
	struct format_code *fmt;
	uint flag_bits = 0;
	long rc = ADAPT_SUCCESS;

	memset(rsp, 0, sizeof(struct srp_login_rsp));

	rsp->opcode = SRP_LOGIN_RSP;
	rsp->req_lim_delta = cpu_to_be32(vscsi->request_limit);
	rsp->tag = cmd->rsp.tag;
	rsp->max_it_iu_len = cpu_to_be32(SRP_MAX_IU_LEN);
	rsp->max_ti_iu_len = cpu_to_be32(SRP_MAX_IU_LEN);
	fmt = (struct format_code *)&rsp->buf_fmt;
	fmt->buffers = SUPPORTED_FORMATS;
	vscsi->credit = 0;

	cmd->rsp.len = sizeof(struct srp_login_rsp);

	dma_wmb();
	rc = h_copy_rdma(cmd->rsp.len, vscsi->dds.window[LOCAL].liobn,
			 iue->sbuf->dma, vscsi->dds.window[REMOTE].liobn,
			 be64_to_cpu(iue->remote_token));

	switch (rc) {
	case H_SUCCESS:
		break;

	case H_PERMISSION:
		if (connection_broken(vscsi))
			flag_bits = RESPONSE_Q_DOWN | CLIENT_FAILED;
		dev_err(&vscsi->dev, "login_rsp: error copying to client, rc %ld\n",
			rc);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT,
					  flag_bits);
		break;
	case H_SOURCE_PARM:
	case H_DEST_PARM:
	default:
		dev_err(&vscsi->dev, "login_rsp: error copying to client, rc %ld\n",
			rc);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT, 0);
		break;
	}

	return rc;
}