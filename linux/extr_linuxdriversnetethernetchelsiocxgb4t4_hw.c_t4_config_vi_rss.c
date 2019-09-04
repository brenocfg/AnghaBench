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
struct TYPE_4__ {void* defaultq_to_udpen; } ;
struct TYPE_3__ {TYPE_2__ basicvirtual; } ;
struct fw_rss_vi_config_cmd {TYPE_1__ u; void* retval_len16; void* op_to_viid; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 unsigned int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 unsigned int FW_CMD_REQUEST_F ; 
 unsigned int FW_CMD_WRITE_F ; 
 unsigned int FW_LEN16 (struct fw_rss_vi_config_cmd) ; 
 int /*<<< orphan*/  FW_RSS_VI_CONFIG_CMD ; 
 unsigned int FW_RSS_VI_CONFIG_CMD_DEFAULTQ_V (unsigned int) ; 
 unsigned int FW_RSS_VI_CONFIG_CMD_VIID_V (unsigned int) ; 
 void* cpu_to_be32 (unsigned int) ; 
 int /*<<< orphan*/  memset (struct fw_rss_vi_config_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox (struct adapter*,int,struct fw_rss_vi_config_cmd*,int,int /*<<< orphan*/ *) ; 

int t4_config_vi_rss(struct adapter *adapter, int mbox, unsigned int viid,
		     unsigned int flags, unsigned int defq)
{
	struct fw_rss_vi_config_cmd c;

	memset(&c, 0, sizeof(c));
	c.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_RSS_VI_CONFIG_CMD) |
				   FW_CMD_REQUEST_F | FW_CMD_WRITE_F |
				   FW_RSS_VI_CONFIG_CMD_VIID_V(viid));
	c.retval_len16 = cpu_to_be32(FW_LEN16(c));
	c.u.basicvirtual.defaultq_to_udpen = cpu_to_be32(flags |
					FW_RSS_VI_CONFIG_CMD_DEFAULTQ_V(defq));
	return t4_wr_mbox(adapter, mbox, &c, sizeof(c), NULL);
}