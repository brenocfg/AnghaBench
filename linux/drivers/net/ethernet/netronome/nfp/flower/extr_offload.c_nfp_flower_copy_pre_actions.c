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
typedef  int u8 ;
struct nfp_fl_act_head {unsigned int len_lw; int jump_id; } ;

/* Variables and functions */
#define  NFP_FL_ACTION_OPCODE_PRE_LAG 129 
#define  NFP_FL_ACTION_OPCODE_PRE_TUNNEL 128 
 unsigned int NFP_FL_LW_SIZ ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned int) ; 

__attribute__((used)) static unsigned int
nfp_flower_copy_pre_actions(char *act_dst, char *act_src, int len,
			    bool *tunnel_act)
{
	unsigned int act_off = 0, act_len;
	struct nfp_fl_act_head *a;
	u8 act_id = 0;

	while (act_off < len) {
		a = (struct nfp_fl_act_head *)&act_src[act_off];
		act_len = a->len_lw << NFP_FL_LW_SIZ;
		act_id = a->jump_id;

		switch (act_id) {
		case NFP_FL_ACTION_OPCODE_PRE_TUNNEL:
			if (tunnel_act)
				*tunnel_act = true;
			/* fall through */
		case NFP_FL_ACTION_OPCODE_PRE_LAG:
			memcpy(act_dst + act_off, act_src + act_off, act_len);
			break;
		default:
			return act_off;
		}

		act_off += act_len;
	}

	return act_off;
}