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
struct cec_adapter {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
#define  CEC_TX_STATUS_ARB_LOST 132 
#define  CEC_TX_STATUS_ERROR 131 
#define  CEC_TX_STATUS_LOW_DRIVE 130 
 int CEC_TX_STATUS_MAX_RETRIES ; 
#define  CEC_TX_STATUS_NACK 129 
#define  CEC_TX_STATUS_OK 128 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cec_transmit_done_ts (struct cec_adapter*,int,int,int,int,int,int /*<<< orphan*/ ) ; 

void cec_transmit_attempt_done_ts(struct cec_adapter *adap,
				  u8 status, ktime_t ts)
{
	switch (status & ~CEC_TX_STATUS_MAX_RETRIES) {
	case CEC_TX_STATUS_OK:
		cec_transmit_done_ts(adap, status, 0, 0, 0, 0, ts);
		return;
	case CEC_TX_STATUS_ARB_LOST:
		cec_transmit_done_ts(adap, status, 1, 0, 0, 0, ts);
		return;
	case CEC_TX_STATUS_NACK:
		cec_transmit_done_ts(adap, status, 0, 1, 0, 0, ts);
		return;
	case CEC_TX_STATUS_LOW_DRIVE:
		cec_transmit_done_ts(adap, status, 0, 0, 1, 0, ts);
		return;
	case CEC_TX_STATUS_ERROR:
		cec_transmit_done_ts(adap, status, 0, 0, 0, 1, ts);
		return;
	default:
		/* Should never happen */
		WARN(1, "cec-%s: invalid status 0x%02x\n", adap->name, status);
		return;
	}
}