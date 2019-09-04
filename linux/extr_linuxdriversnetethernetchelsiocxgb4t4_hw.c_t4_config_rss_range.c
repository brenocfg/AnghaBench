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
typedef  int /*<<< orphan*/  u16 ;
struct fw_rss_ind_tbl_cmd {void* startidx; void* niqid; int /*<<< orphan*/  iq0_to_iq2; void* retval_len16; void* op_to_viid; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 unsigned int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 unsigned int FW_CMD_REQUEST_F ; 
 unsigned int FW_CMD_WRITE_F ; 
 unsigned int FW_LEN16 (struct fw_rss_ind_tbl_cmd) ; 
 int /*<<< orphan*/  FW_RSS_IND_TBL_CMD ; 
 unsigned int FW_RSS_IND_TBL_CMD_IQ0_V (int /*<<< orphan*/  const) ; 
 unsigned int FW_RSS_IND_TBL_CMD_IQ1_V (int /*<<< orphan*/  const) ; 
 unsigned int FW_RSS_IND_TBL_CMD_IQ2_V (int /*<<< orphan*/  const) ; 
 unsigned int FW_RSS_IND_TBL_CMD_VIID_V (unsigned int) ; 
 void* cpu_to_be16 (int) ; 
 void* cpu_to_be32 (unsigned int) ; 
 int /*<<< orphan*/  memset (struct fw_rss_ind_tbl_cmd*,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 int t4_wr_mbox (struct adapter*,int,struct fw_rss_ind_tbl_cmd*,int,int /*<<< orphan*/ *) ; 

int t4_config_rss_range(struct adapter *adapter, int mbox, unsigned int viid,
			int start, int n, const u16 *rspq, unsigned int nrspq)
{
	int ret;
	const u16 *rsp = rspq;
	const u16 *rsp_end = rspq + nrspq;
	struct fw_rss_ind_tbl_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_RSS_IND_TBL_CMD) |
			       FW_CMD_REQUEST_F | FW_CMD_WRITE_F |
			       FW_RSS_IND_TBL_CMD_VIID_V(viid));
	cmd.retval_len16 = cpu_to_be32(FW_LEN16(cmd));

	/* each fw_rss_ind_tbl_cmd takes up to 32 entries */
	while (n > 0) {
		int nq = min(n, 32);
		__be32 *qp = &cmd.iq0_to_iq2;

		cmd.niqid = cpu_to_be16(nq);
		cmd.startidx = cpu_to_be16(start);

		start += nq;
		n -= nq;

		while (nq > 0) {
			unsigned int v;

			v = FW_RSS_IND_TBL_CMD_IQ0_V(*rsp);
			if (++rsp >= rsp_end)
				rsp = rspq;
			v |= FW_RSS_IND_TBL_CMD_IQ1_V(*rsp);
			if (++rsp >= rsp_end)
				rsp = rspq;
			v |= FW_RSS_IND_TBL_CMD_IQ2_V(*rsp);
			if (++rsp >= rsp_end)
				rsp = rspq;

			*qp++ = cpu_to_be32(v);
			nq -= 3;
		}

		ret = t4_wr_mbox(adapter, mbox, &cmd, sizeof(cmd), NULL);
		if (ret)
			return ret;
	}
	return 0;
}