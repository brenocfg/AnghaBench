#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/ * cec_message; } ;
struct TYPE_5__ {TYPE_1__ data; } ;
struct cros_ec_device {unsigned int event_size; TYPE_2__ event_data; } ;
struct TYPE_6__ {unsigned int len; int /*<<< orphan*/  msg; } ;
struct cros_ec_cec {TYPE_3__ rx_msg; int /*<<< orphan*/  adap; struct cros_ec_device* cros_ec; } ;

/* Variables and functions */
 int /*<<< orphan*/  cec_received_msg (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void handle_cec_message(struct cros_ec_cec *cros_ec_cec)
{
	struct cros_ec_device *cros_ec = cros_ec_cec->cros_ec;
	uint8_t *cec_message = cros_ec->event_data.data.cec_message;
	unsigned int len = cros_ec->event_size;

	cros_ec_cec->rx_msg.len = len;
	memcpy(cros_ec_cec->rx_msg.msg, cec_message, len);

	cec_received_msg(cros_ec_cec->adap, &cros_ec_cec->rx_msg);
}