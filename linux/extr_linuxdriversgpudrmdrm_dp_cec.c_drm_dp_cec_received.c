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
typedef  int u8 ;
struct TYPE_2__ {struct cec_adapter* adap; } ;
struct drm_dp_aux {TYPE_1__ cec; } ;
struct cec_msg {int len; int /*<<< orphan*/  msg; } ;
struct cec_adapter {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_CEC_RX_MESSAGE_BUFFER ; 
 int DP_CEC_RX_MESSAGE_ENDED ; 
 int /*<<< orphan*/  DP_CEC_RX_MESSAGE_INFO ; 
 int DP_CEC_RX_MESSAGE_LEN_MASK ; 
 int /*<<< orphan*/  cec_received_msg (struct cec_adapter*,struct cec_msg*) ; 
 scalar_t__ drm_dp_dpcd_read (struct drm_dp_aux*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ drm_dp_dpcd_readb (struct drm_dp_aux*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int drm_dp_cec_received(struct drm_dp_aux *aux)
{
	struct cec_adapter *adap = aux->cec.adap;
	struct cec_msg msg;
	u8 rx_msg_info;
	ssize_t err;

	err = drm_dp_dpcd_readb(aux, DP_CEC_RX_MESSAGE_INFO, &rx_msg_info);
	if (err < 0)
		return err;

	if (!(rx_msg_info & DP_CEC_RX_MESSAGE_ENDED))
		return 0;

	msg.len = (rx_msg_info & DP_CEC_RX_MESSAGE_LEN_MASK) + 1;
	err = drm_dp_dpcd_read(aux, DP_CEC_RX_MESSAGE_BUFFER, msg.msg, msg.len);
	if (err < 0)
		return err;

	cec_received_msg(adap, &msg);
	return 0;
}