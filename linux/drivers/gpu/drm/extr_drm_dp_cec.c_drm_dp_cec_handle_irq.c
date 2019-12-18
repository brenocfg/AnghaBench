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
struct cec_adapter {int dummy; } ;

/* Variables and functions */
 int CEC_TX_STATUS_ERROR ; 
 int CEC_TX_STATUS_MAX_RETRIES ; 
 int CEC_TX_STATUS_NACK ; 
 int CEC_TX_STATUS_OK ; 
 int DP_CEC_RX_MESSAGE_INFO_VALID ; 
 int /*<<< orphan*/  DP_CEC_TUNNELING_IRQ_FLAGS ; 
 int DP_CEC_TX_ADDRESS_NACK_ERROR ; 
 int DP_CEC_TX_DATA_NACK_ERROR ; 
 int DP_CEC_TX_LINE_ERROR ; 
 int DP_CEC_TX_MESSAGE_SENT ; 
 int /*<<< orphan*/  cec_transmit_attempt_done (struct cec_adapter*,int) ; 
 int /*<<< orphan*/  drm_dp_cec_received (struct drm_dp_aux*) ; 
 scalar_t__ drm_dp_dpcd_readb (struct drm_dp_aux*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  drm_dp_dpcd_writeb (struct drm_dp_aux*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void drm_dp_cec_handle_irq(struct drm_dp_aux *aux)
{
	struct cec_adapter *adap = aux->cec.adap;
	u8 flags;

	if (drm_dp_dpcd_readb(aux, DP_CEC_TUNNELING_IRQ_FLAGS, &flags) < 0)
		return;

	if (flags & DP_CEC_RX_MESSAGE_INFO_VALID)
		drm_dp_cec_received(aux);

	if (flags & DP_CEC_TX_MESSAGE_SENT)
		cec_transmit_attempt_done(adap, CEC_TX_STATUS_OK);
	else if (flags & DP_CEC_TX_LINE_ERROR)
		cec_transmit_attempt_done(adap, CEC_TX_STATUS_ERROR |
						CEC_TX_STATUS_MAX_RETRIES);
	else if (flags &
		 (DP_CEC_TX_ADDRESS_NACK_ERROR | DP_CEC_TX_DATA_NACK_ERROR))
		cec_transmit_attempt_done(adap, CEC_TX_STATUS_NACK |
						CEC_TX_STATUS_MAX_RETRIES);
	drm_dp_dpcd_writeb(aux, DP_CEC_TUNNELING_IRQ_FLAGS, flags);
}