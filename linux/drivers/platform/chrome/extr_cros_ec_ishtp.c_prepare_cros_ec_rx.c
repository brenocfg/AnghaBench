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
typedef  scalar_t__ u8 ;
struct ec_host_response {int dummy; } ;
struct TYPE_2__ {int data_len; int /*<<< orphan*/  result; } ;
struct cros_ish_in_msg {TYPE_1__ ec_response; } ;
struct cros_ec_device {int /*<<< orphan*/  dev; } ;
struct cros_ec_command {int insize; scalar_t__* data; int /*<<< orphan*/  result; } ;

/* Variables and functions */
 int EBADMSG ; 
 int ENOSPC ; 
 int IN_MSG_EC_RESPONSE_PREAMBLE ; 
 int cros_ec_check_result (struct cros_ec_device*,struct cros_ec_command*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int prepare_cros_ec_rx(struct cros_ec_device *ec_dev,
			      const struct cros_ish_in_msg *in_msg,
			      struct cros_ec_command *msg)
{
	u8 sum = 0;
	int i, rv, offset;

	/* Check response error code */
	msg->result = in_msg->ec_response.result;
	rv = cros_ec_check_result(ec_dev, msg);
	if (rv < 0)
		return rv;

	if (in_msg->ec_response.data_len > msg->insize) {
		dev_err(ec_dev->dev, "Packet too long (%d bytes, expected %d)",
			in_msg->ec_response.data_len, msg->insize);
		return -ENOSPC;
	}

	/* Copy response packet payload and compute checksum */
	for (i = 0; i < sizeof(struct ec_host_response); i++)
		sum += ((u8 *)in_msg)[IN_MSG_EC_RESPONSE_PREAMBLE + i];

	offset = sizeof(struct cros_ish_in_msg);
	for (i = 0; i < in_msg->ec_response.data_len; i++)
		sum += msg->data[i] = ((u8 *)in_msg)[offset + i];

	if (sum) {
		dev_dbg(ec_dev->dev, "Bad received packet checksum %d\n", sum);
		return -EBADMSG;
	}

	return 0;
}