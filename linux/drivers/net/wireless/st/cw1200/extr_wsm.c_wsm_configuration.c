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
struct wsm_configuration {int dpdData_size; int /*<<< orphan*/  dpdData; int /*<<< orphan*/  dot11StationId; int /*<<< orphan*/  dot11RtsThreshold; int /*<<< orphan*/  dot11MaxReceiveLifeTime; int /*<<< orphan*/  dot11MaxTransmitMsduLifeTime; } ;
struct wsm_buf {int dummy; } ;
struct cw1200_common {struct wsm_buf wsm_cmd_buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  WSM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  WSM_CONFIGURATION_REQ_ID ; 
 int /*<<< orphan*/  WSM_PUT (struct wsm_buf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WSM_PUT16 (struct wsm_buf*,int) ; 
 int /*<<< orphan*/  WSM_PUT32 (struct wsm_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsm_cmd_lock (struct cw1200_common*) ; 
 int wsm_cmd_send (struct cw1200_common*,struct wsm_buf*,struct wsm_configuration*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsm_cmd_unlock (struct cw1200_common*) ; 

int wsm_configuration(struct cw1200_common *priv, struct wsm_configuration *arg)
{
	int ret;
	struct wsm_buf *buf = &priv->wsm_cmd_buf;

	wsm_cmd_lock(priv);

	WSM_PUT32(buf, arg->dot11MaxTransmitMsduLifeTime);
	WSM_PUT32(buf, arg->dot11MaxReceiveLifeTime);
	WSM_PUT32(buf, arg->dot11RtsThreshold);

	/* DPD block. */
	WSM_PUT16(buf, arg->dpdData_size + 12);
	WSM_PUT16(buf, 1); /* DPD version */
	WSM_PUT(buf, arg->dot11StationId, ETH_ALEN);
	WSM_PUT16(buf, 5); /* DPD flags */
	WSM_PUT(buf, arg->dpdData, arg->dpdData_size);

	ret = wsm_cmd_send(priv, buf, arg,
			   WSM_CONFIGURATION_REQ_ID, WSM_CMD_TIMEOUT);

	wsm_cmd_unlock(priv);
	return ret;

nomem:
	wsm_cmd_unlock(priv);
	return -ENOMEM;
}