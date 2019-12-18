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
struct spi_packet {scalar_t__ device; } ;
struct message {int /*<<< orphan*/  rsp_buf_len; int /*<<< orphan*/  type; int /*<<< orphan*/  length; int /*<<< orphan*/  tp_info; } ;
struct applespi_data {TYPE_1__* spi; int /*<<< orphan*/  work; int /*<<< orphan*/  rcvd_tp_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ PACKET_DEV_INFO ; 
 scalar_t__ PACKET_DEV_TPAD ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn_ratelimited (int /*<<< orphan*/ *,char*,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void applespi_handle_cmd_response(struct applespi_data *applespi,
					 struct spi_packet *packet,
					 struct message *message)
{
	if (packet->device == PACKET_DEV_INFO &&
	    le16_to_cpu(message->type) == 0x1020) {
		/*
		 * We're not allowed to sleep here, but registering an input
		 * device can sleep.
		 */
		applespi->rcvd_tp_info = message->tp_info;
		schedule_work(&applespi->work);
		return;
	}

	if (le16_to_cpu(message->length) != 0x0000) {
		dev_warn_ratelimited(&applespi->spi->dev,
				     "Received unexpected write response: length=%x\n",
				     le16_to_cpu(message->length));
		return;
	}

	if (packet->device == PACKET_DEV_TPAD &&
	    le16_to_cpu(message->type) == 0x0252 &&
	    le16_to_cpu(message->rsp_buf_len) == 0x0002)
		dev_info(&applespi->spi->dev, "modeswitch done.\n");
}