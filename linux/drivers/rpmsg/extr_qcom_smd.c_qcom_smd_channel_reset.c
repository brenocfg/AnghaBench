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
struct qcom_smd_channel {scalar_t__ pkt_size; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_RX_CHANNEL_INFO (struct qcom_smd_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_CHANNEL_FLAG (struct qcom_smd_channel*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET_TX_CHANNEL_INFO (struct qcom_smd_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMD_CHANNEL_CLOSED ; 
 int /*<<< orphan*/  fBLOCKREADINTR ; 
 int /*<<< orphan*/  fCD ; 
 int /*<<< orphan*/  fCTS ; 
 int /*<<< orphan*/  fDSR ; 
 int /*<<< orphan*/  fHEAD ; 
 int /*<<< orphan*/  fRI ; 
 int /*<<< orphan*/  fSTATE ; 
 int /*<<< orphan*/  fTAIL ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  qcom_smd_signal_channel (struct qcom_smd_channel*) ; 
 int /*<<< orphan*/  state ; 
 int /*<<< orphan*/  tail ; 

__attribute__((used)) static void qcom_smd_channel_reset(struct qcom_smd_channel *channel)
{
	SET_TX_CHANNEL_INFO(channel, state, SMD_CHANNEL_CLOSED);
	SET_TX_CHANNEL_FLAG(channel, fDSR, 0);
	SET_TX_CHANNEL_FLAG(channel, fCTS, 0);
	SET_TX_CHANNEL_FLAG(channel, fCD, 0);
	SET_TX_CHANNEL_FLAG(channel, fRI, 0);
	SET_TX_CHANNEL_FLAG(channel, fHEAD, 0);
	SET_TX_CHANNEL_FLAG(channel, fTAIL, 0);
	SET_TX_CHANNEL_FLAG(channel, fSTATE, 1);
	SET_TX_CHANNEL_FLAG(channel, fBLOCKREADINTR, 1);
	SET_TX_CHANNEL_INFO(channel, head, 0);
	SET_RX_CHANNEL_INFO(channel, tail, 0);

	qcom_smd_signal_channel(channel);

	channel->state = SMD_CHANNEL_CLOSED;
	channel->pkt_size = 0;
}