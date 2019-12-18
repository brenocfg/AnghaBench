#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qla_tgt_prm {scalar_t__ seg_cnt; int /*<<< orphan*/  sg; TYPE_1__* cmd; scalar_t__ pkt; } ;
struct dsd64 {scalar_t__ length; scalar_t__ address; } ;
struct TYPE_5__ {struct dsd64 dsd; int /*<<< orphan*/  transfer_length; } ;
struct TYPE_6__ {TYPE_2__ status0; } ;
struct ctio7_to_24xx {int /*<<< orphan*/  dseg_count; TYPE_3__ u; } ;
struct TYPE_4__ {int /*<<< orphan*/  bufflen; } ;

/* Variables and functions */
 int QLA_TGT_DATASEGS_PER_CMD_24XX ; 
 int /*<<< orphan*/  append_dsd64 (struct dsd64**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlt_load_cont_data_segments (struct qla_tgt_prm*) ; 
 int /*<<< orphan*/  sg_next (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qlt_load_data_segments(struct qla_tgt_prm *prm)
{
	int cnt;
	struct dsd64 *cur_dsd;
	struct ctio7_to_24xx *pkt24 = (struct ctio7_to_24xx *)prm->pkt;

	pkt24->u.status0.transfer_length = cpu_to_le32(prm->cmd->bufflen);

	/* Setup packet address segment pointer */
	cur_dsd = &pkt24->u.status0.dsd;

	/* Set total data segment count */
	if (prm->seg_cnt)
		pkt24->dseg_count = cpu_to_le16(prm->seg_cnt);

	if (prm->seg_cnt == 0) {
		/* No data transfer */
		cur_dsd->address = 0;
		cur_dsd->length = 0;
		return;
	}

	/* If scatter gather */

	/* Load command entry data segments */
	for (cnt = 0;
	    (cnt < QLA_TGT_DATASEGS_PER_CMD_24XX) && prm->seg_cnt;
	    cnt++, prm->seg_cnt--) {
		append_dsd64(&cur_dsd, prm->sg);
		prm->sg = sg_next(prm->sg);
	}

	qlt_load_cont_data_segments(prm);
}