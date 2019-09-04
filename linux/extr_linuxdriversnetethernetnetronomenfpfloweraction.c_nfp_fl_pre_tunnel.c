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
struct TYPE_2__ {size_t len_lw; int /*<<< orphan*/  jump_id; } ;
struct nfp_fl_pre_tunnel {TYPE_1__ head; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_FL_ACTION_OPCODE_PRE_TUNNEL ; 
 size_t NFP_FL_LW_SIZ ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int /*<<< orphan*/  memset (struct nfp_fl_pre_tunnel*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static struct nfp_fl_pre_tunnel *nfp_fl_pre_tunnel(char *act_data, int act_len)
{
	size_t act_size = sizeof(struct nfp_fl_pre_tunnel);
	struct nfp_fl_pre_tunnel *pre_tun_act;

	/* Pre_tunnel action must be first on action list.
	 * If other actions already exist they need to be pushed forward.
	 */
	if (act_len)
		memmove(act_data + act_size, act_data, act_len);

	pre_tun_act = (struct nfp_fl_pre_tunnel *)act_data;

	memset(pre_tun_act, 0, act_size);

	pre_tun_act->head.jump_id = NFP_FL_ACTION_OPCODE_PRE_TUNNEL;
	pre_tun_act->head.len_lw = act_size >> NFP_FL_LW_SIZ;

	return pre_tun_act;
}