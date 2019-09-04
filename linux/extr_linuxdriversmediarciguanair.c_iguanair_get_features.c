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
struct iguanair {int version; int bufsize; int cycle_overhead; int /*<<< orphan*/  dev; TYPE_2__* packet; } ;
struct TYPE_3__ {int /*<<< orphan*/  cmd; int /*<<< orphan*/  direction; scalar_t__ start; } ;
struct TYPE_4__ {TYPE_1__ header; } ;

/* Variables and functions */
 int BUF_SIZE ; 
 int /*<<< orphan*/  CMD_GET_BUFSIZE ; 
 int /*<<< orphan*/  CMD_GET_FEATURES ; 
 int /*<<< orphan*/  CMD_GET_VERSION ; 
 int /*<<< orphan*/  CMD_NOP ; 
 int /*<<< orphan*/  DIR_OUT ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int iguanair_send (struct iguanair*,int) ; 

__attribute__((used)) static int iguanair_get_features(struct iguanair *ir)
{
	int rc;

	/*
	 * On cold boot, the iguanair initializes on the first packet
	 * received but does not process that packet. Send an empty
	 * packet.
	 */
	ir->packet->header.start = 0;
	ir->packet->header.direction = DIR_OUT;
	ir->packet->header.cmd = CMD_NOP;
	iguanair_send(ir, sizeof(ir->packet->header));

	ir->packet->header.cmd = CMD_GET_VERSION;
	rc = iguanair_send(ir, sizeof(ir->packet->header));
	if (rc) {
		dev_info(ir->dev, "failed to get version\n");
		goto out;
	}

	if (ir->version < 0x205) {
		dev_err(ir->dev, "firmware 0x%04x is too old\n", ir->version);
		rc = -ENODEV;
		goto out;
	}

	ir->bufsize = 150;
	ir->cycle_overhead = 65;

	ir->packet->header.cmd = CMD_GET_BUFSIZE;

	rc = iguanair_send(ir, sizeof(ir->packet->header));
	if (rc) {
		dev_info(ir->dev, "failed to get buffer size\n");
		goto out;
	}

	if (ir->bufsize > BUF_SIZE) {
		dev_info(ir->dev, "buffer size %u larger than expected\n",
								ir->bufsize);
		ir->bufsize = BUF_SIZE;
	}

	ir->packet->header.cmd = CMD_GET_FEATURES;

	rc = iguanair_send(ir, sizeof(ir->packet->header));
	if (rc)
		dev_info(ir->dev, "failed to get features\n");
out:
	return rc;
}