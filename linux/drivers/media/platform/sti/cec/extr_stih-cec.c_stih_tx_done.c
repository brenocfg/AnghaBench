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
typedef  int u32 ;
struct stih_cec {int /*<<< orphan*/  adap; } ;

/* Variables and functions */
 int CEC_TX_ACK_GET_STS ; 
 int CEC_TX_ARB_ERROR ; 
 int CEC_TX_ERROR ; 
 int /*<<< orphan*/  CEC_TX_STATUS_ARB_LOST ; 
 int /*<<< orphan*/  CEC_TX_STATUS_ERROR ; 
 int /*<<< orphan*/  CEC_TX_STATUS_NACK ; 
 int /*<<< orphan*/  CEC_TX_STATUS_OK ; 
 int /*<<< orphan*/  cec_transmit_attempt_done (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stih_tx_done(struct stih_cec *cec, u32 status)
{
	if (status & CEC_TX_ERROR) {
		cec_transmit_attempt_done(cec->adap, CEC_TX_STATUS_ERROR);
		return;
	}

	if (status & CEC_TX_ARB_ERROR) {
		cec_transmit_attempt_done(cec->adap, CEC_TX_STATUS_ARB_LOST);
		return;
	}

	if (!(status & CEC_TX_ACK_GET_STS)) {
		cec_transmit_attempt_done(cec->adap, CEC_TX_STATUS_NACK);
		return;
	}

	cec_transmit_attempt_done(cec->adap, CEC_TX_STATUS_OK);
}