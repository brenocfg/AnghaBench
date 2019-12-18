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
struct mcu_msg_init_request {int suballoc_dma; size_t suballoc_size; int* l2_cache; TYPE_1__ header; } ;
struct allegro_dev {int /*<<< orphan*/  mbox_command; } ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int MCU_CACHE_OFFSET ; 
 int /*<<< orphan*/  MCU_MSG_TYPE_INIT ; 
 int /*<<< orphan*/  allegro_mbox_write (struct allegro_dev*,int /*<<< orphan*/ *,struct mcu_msg_init_request*,int) ; 
 int /*<<< orphan*/  allegro_mcu_interrupt (struct allegro_dev*) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mcu_msg_init_request*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void allegro_mcu_send_init(struct allegro_dev *dev,
				  dma_addr_t suballoc_dma, size_t suballoc_size)
{
	struct mcu_msg_init_request msg;

	memset(&msg, 0, sizeof(msg));

	msg.header.type = MCU_MSG_TYPE_INIT;
	msg.header.length = sizeof(msg) - sizeof(msg.header);

	msg.suballoc_dma = lower_32_bits(suballoc_dma) | MCU_CACHE_OFFSET;
	msg.suballoc_size = suballoc_size;

	/* disable L2 cache */
	msg.l2_cache[0] = -1;
	msg.l2_cache[1] = -1;
	msg.l2_cache[2] = -1;

	allegro_mbox_write(dev, &dev->mbox_command, &msg, sizeof(msg));
	allegro_mcu_interrupt(dev);
}