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
struct wsm_edca_params {TYPE_1__* params; } ;
struct wsm_buf {int dummy; } ;
struct cw1200_common {struct wsm_buf wsm_cmd_buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_rx_lifetime; int /*<<< orphan*/  txop_limit; int /*<<< orphan*/  aifns; int /*<<< orphan*/  cwmax; int /*<<< orphan*/  cwmin; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  WSM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  WSM_EDCA_PARAMS_REQ_ID ; 
 int /*<<< orphan*/  WSM_PUT16 (struct wsm_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSM_PUT32 (struct wsm_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSM_PUT8 (struct wsm_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsm_cmd_lock (struct cw1200_common*) ; 
 int wsm_cmd_send (struct cw1200_common*,struct wsm_buf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsm_cmd_unlock (struct cw1200_common*) ; 

int wsm_set_edca_params(struct cw1200_common *priv,
				const struct wsm_edca_params *arg)
{
	int ret;
	struct wsm_buf *buf = &priv->wsm_cmd_buf;

	wsm_cmd_lock(priv);

	/* Implemented according to specification. */

	WSM_PUT16(buf, arg->params[3].cwmin);
	WSM_PUT16(buf, arg->params[2].cwmin);
	WSM_PUT16(buf, arg->params[1].cwmin);
	WSM_PUT16(buf, arg->params[0].cwmin);

	WSM_PUT16(buf, arg->params[3].cwmax);
	WSM_PUT16(buf, arg->params[2].cwmax);
	WSM_PUT16(buf, arg->params[1].cwmax);
	WSM_PUT16(buf, arg->params[0].cwmax);

	WSM_PUT8(buf, arg->params[3].aifns);
	WSM_PUT8(buf, arg->params[2].aifns);
	WSM_PUT8(buf, arg->params[1].aifns);
	WSM_PUT8(buf, arg->params[0].aifns);

	WSM_PUT16(buf, arg->params[3].txop_limit);
	WSM_PUT16(buf, arg->params[2].txop_limit);
	WSM_PUT16(buf, arg->params[1].txop_limit);
	WSM_PUT16(buf, arg->params[0].txop_limit);

	WSM_PUT32(buf, arg->params[3].max_rx_lifetime);
	WSM_PUT32(buf, arg->params[2].max_rx_lifetime);
	WSM_PUT32(buf, arg->params[1].max_rx_lifetime);
	WSM_PUT32(buf, arg->params[0].max_rx_lifetime);

	ret = wsm_cmd_send(priv, buf, NULL,
			   WSM_EDCA_PARAMS_REQ_ID, WSM_CMD_TIMEOUT);
	wsm_cmd_unlock(priv);
	return ret;

nomem:
	wsm_cmd_unlock(priv);
	return -ENOMEM;
}