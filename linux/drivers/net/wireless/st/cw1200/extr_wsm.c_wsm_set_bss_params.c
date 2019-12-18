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
struct wsm_set_bss_params {int beacon_lost_count; int /*<<< orphan*/  operational_rate_set; int /*<<< orphan*/  aid; scalar_t__ reset_beacon_loss; } ;
struct wsm_buf {int dummy; } ;
struct cw1200_common {struct wsm_buf wsm_cmd_buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  WSM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  WSM_PUT16 (struct wsm_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSM_PUT32 (struct wsm_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSM_PUT8 (struct wsm_buf*,int) ; 
 int /*<<< orphan*/  WSM_SET_BSS_PARAMS_REQ_ID ; 
 int /*<<< orphan*/  wsm_cmd_lock (struct cw1200_common*) ; 
 int wsm_cmd_send (struct cw1200_common*,struct wsm_buf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsm_cmd_unlock (struct cw1200_common*) ; 

int wsm_set_bss_params(struct cw1200_common *priv,
		       const struct wsm_set_bss_params *arg)
{
	int ret;
	struct wsm_buf *buf = &priv->wsm_cmd_buf;

	wsm_cmd_lock(priv);

	WSM_PUT8(buf, (arg->reset_beacon_loss ?  0x1 : 0));
	WSM_PUT8(buf, arg->beacon_lost_count);
	WSM_PUT16(buf, arg->aid);
	WSM_PUT32(buf, arg->operational_rate_set);

	ret = wsm_cmd_send(priv, buf, NULL,
			   WSM_SET_BSS_PARAMS_REQ_ID, WSM_CMD_TIMEOUT);

	wsm_cmd_unlock(priv);
	return ret;

nomem:
	wsm_cmd_unlock(priv);
	return -ENOMEM;
}