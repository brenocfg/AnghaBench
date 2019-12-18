#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int cec_events; } ;
struct TYPE_4__ {TYPE_1__ data; } ;
struct cros_ec_device {TYPE_2__ event_data; } ;
struct cros_ec_cec {int /*<<< orphan*/  adap; struct cros_ec_device* cros_ec; } ;

/* Variables and functions */
 int CEC_TX_STATUS_MAX_RETRIES ; 
 int CEC_TX_STATUS_NACK ; 
 int CEC_TX_STATUS_OK ; 
 int EC_MKBP_CEC_SEND_FAILED ; 
 int EC_MKBP_CEC_SEND_OK ; 
 int /*<<< orphan*/  cec_transmit_attempt_done (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void handle_cec_event(struct cros_ec_cec *cros_ec_cec)
{
	struct cros_ec_device *cros_ec = cros_ec_cec->cros_ec;
	uint32_t events = cros_ec->event_data.data.cec_events;

	if (events & EC_MKBP_CEC_SEND_OK)
		cec_transmit_attempt_done(cros_ec_cec->adap,
					  CEC_TX_STATUS_OK);

	/* FW takes care of all retries, tell core to avoid more retries */
	if (events & EC_MKBP_CEC_SEND_FAILED)
		cec_transmit_attempt_done(cros_ec_cec->adap,
					  CEC_TX_STATUS_MAX_RETRIES |
					  CEC_TX_STATUS_NACK);
}