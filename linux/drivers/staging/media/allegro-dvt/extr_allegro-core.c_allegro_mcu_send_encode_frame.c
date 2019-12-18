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
struct TYPE_2__ {int length; int /*<<< orphan*/  type; } ;
struct mcu_msg_encode_frame {int pps_qp; int ep2; int ep2_v; int /*<<< orphan*/  stride; void* src_uv; void* src_y; scalar_t__ src_handle; scalar_t__ user_param; int /*<<< orphan*/  encoding_options; int /*<<< orphan*/  channel_id; TYPE_1__ header; } ;
struct allegro_dev {int /*<<< orphan*/  mbox_command; } ;
struct allegro_channel {int /*<<< orphan*/  stride; int /*<<< orphan*/  mcu_channel_id; } ;
typedef  int /*<<< orphan*/  msg ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AL_OPT_FORCE_LOAD ; 
 int MCU_CACHE_OFFSET ; 
 int /*<<< orphan*/  MCU_MSG_TYPE_ENCODE_FRAME ; 
 int /*<<< orphan*/  allegro_mbox_write (struct allegro_dev*,int /*<<< orphan*/ *,struct mcu_msg_encode_frame*,int) ; 
 int /*<<< orphan*/  allegro_mcu_interrupt (struct allegro_dev*) ; 
 int /*<<< orphan*/  memset (struct mcu_msg_encode_frame*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int allegro_mcu_send_encode_frame(struct allegro_dev *dev,
					 struct allegro_channel *channel,
					 dma_addr_t src_y, dma_addr_t src_uv)
{
	struct mcu_msg_encode_frame msg;

	memset(&msg, 0, sizeof(msg));

	msg.header.type = MCU_MSG_TYPE_ENCODE_FRAME;
	msg.header.length = sizeof(msg) - sizeof(msg.header);

	msg.channel_id = channel->mcu_channel_id;
	msg.encoding_options = AL_OPT_FORCE_LOAD;
	msg.pps_qp = 26; /* qp are relative to 26 */
	msg.user_param = 0; /* copied to mcu_msg_encode_frame_response */
	msg.src_handle = 0; /* copied to mcu_msg_encode_frame_response */
	msg.src_y = src_y;
	msg.src_uv = src_uv;
	msg.stride = channel->stride;
	msg.ep2 = 0x0;
	msg.ep2_v = msg.ep2 | MCU_CACHE_OFFSET;

	allegro_mbox_write(dev, &dev->mbox_command, &msg, sizeof(msg));
	allegro_mcu_interrupt(dev);

	return 0;
}