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
struct ec_lpc_host_args {scalar_t__ flags; scalar_t__ command_version; scalar_t__ data_size; scalar_t__ checksum; } ;
struct cros_ec_device {int /*<<< orphan*/  dev; } ;
struct cros_ec_command {scalar_t__ outsize; scalar_t__ insize; scalar_t__ version; scalar_t__ command; scalar_t__* data; scalar_t__ result; } ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_2__ {scalar_t__ (* read ) (int /*<<< orphan*/ ,int,scalar_t__*) ;int /*<<< orphan*/  (* write ) (int /*<<< orphan*/ ,int,scalar_t__*) ;} ;

/* Variables and functions */
 int EBADMSG ; 
 scalar_t__ EC_HOST_ARGS_FLAG_FROM_HOST ; 
 int /*<<< orphan*/  EC_LPC_ADDR_HOST_ARGS ; 
 int /*<<< orphan*/  EC_LPC_ADDR_HOST_CMD ; 
 int /*<<< orphan*/  EC_LPC_ADDR_HOST_DATA ; 
 int /*<<< orphan*/  EC_LPC_ADDR_HOST_PARAM ; 
 scalar_t__ EC_PROTO2_MAX_PARAM_SIZE ; 
 int EINVAL ; 
 int EIO ; 
 int ENOSPC ; 
 int cros_ec_check_result (struct cros_ec_device*,struct cros_ec_command*) ; 
 TYPE_1__ cros_ec_lpc_ops ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ec_response_timed_out () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 scalar_t__ stub4 (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 scalar_t__ stub5 (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 scalar_t__ stub6 (int /*<<< orphan*/ ,int,scalar_t__*) ; 

__attribute__((used)) static int cros_ec_cmd_xfer_lpc(struct cros_ec_device *ec,
				struct cros_ec_command *msg)
{
	struct ec_lpc_host_args args;
	u8 sum;
	int ret = 0;

	if (msg->outsize > EC_PROTO2_MAX_PARAM_SIZE ||
	    msg->insize > EC_PROTO2_MAX_PARAM_SIZE) {
		dev_err(ec->dev,
			"invalid buffer sizes (out %d, in %d)\n",
			msg->outsize, msg->insize);
		return -EINVAL;
	}

	/* Now actually send the command to the EC and get the result */
	args.flags = EC_HOST_ARGS_FLAG_FROM_HOST;
	args.command_version = msg->version;
	args.data_size = msg->outsize;

	/* Initialize checksum */
	sum = msg->command + args.flags + args.command_version + args.data_size;

	/* Copy data and update checksum */
	sum += cros_ec_lpc_ops.write(EC_LPC_ADDR_HOST_PARAM, msg->outsize,
				     msg->data);

	/* Finalize checksum and write args */
	args.checksum = sum;
	cros_ec_lpc_ops.write(EC_LPC_ADDR_HOST_ARGS, sizeof(args),
			      (u8 *)&args);

	/* Here we go */
	sum = msg->command;
	cros_ec_lpc_ops.write(EC_LPC_ADDR_HOST_CMD, 1, &sum);

	if (ec_response_timed_out()) {
		dev_warn(ec->dev, "EC responsed timed out\n");
		ret = -EIO;
		goto done;
	}

	/* Check result */
	msg->result = cros_ec_lpc_ops.read(EC_LPC_ADDR_HOST_DATA, 1, &sum);
	ret = cros_ec_check_result(ec, msg);
	if (ret)
		goto done;

	/* Read back args */
	cros_ec_lpc_ops.read(EC_LPC_ADDR_HOST_ARGS, sizeof(args), (u8 *)&args);

	if (args.data_size > msg->insize) {
		dev_err(ec->dev,
			"packet too long (%d bytes, expected %d)",
			args.data_size, msg->insize);
		ret = -ENOSPC;
		goto done;
	}

	/* Start calculating response checksum */
	sum = msg->command + args.flags + args.command_version + args.data_size;

	/* Read response and update checksum */
	sum += cros_ec_lpc_ops.read(EC_LPC_ADDR_HOST_PARAM, args.data_size,
				    msg->data);

	/* Verify checksum */
	if (args.checksum != sum) {
		dev_err(ec->dev,
			"bad packet checksum, expected %02x, got %02x\n",
			args.checksum, sum);
		ret = -EBADMSG;
		goto done;
	}

	/* Return actual amount of data received */
	ret = args.data_size;
done:
	return ret;
}