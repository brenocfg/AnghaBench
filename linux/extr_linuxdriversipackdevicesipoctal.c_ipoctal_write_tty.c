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
struct tty_struct {struct ipoctal_channel* driver_data; } ;
struct ipoctal_channel {scalar_t__ board_id; TYPE_2__* regs; scalar_t__ rx_enable; } ;
struct TYPE_3__ {int /*<<< orphan*/  cr; } ;
struct TYPE_4__ {TYPE_1__ w; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_CMD_ASSERT_RTSN ; 
 int /*<<< orphan*/  CR_DISABLE_RX ; 
 int /*<<< orphan*/  CR_ENABLE_TX ; 
 scalar_t__ IPACK1_DEVICE_ID_SBS_OCTAL_485 ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int ipoctal_copy_write_buffer (struct ipoctal_channel*,unsigned char const*,int) ; 

__attribute__((used)) static int ipoctal_write_tty(struct tty_struct *tty,
			     const unsigned char *buf, int count)
{
	struct ipoctal_channel *channel = tty->driver_data;
	unsigned int char_copied;

	char_copied = ipoctal_copy_write_buffer(channel, buf, count);

	/* As the IP-OCTAL 485 only supports half duplex, do it manually */
	if (channel->board_id == IPACK1_DEVICE_ID_SBS_OCTAL_485) {
		iowrite8(CR_DISABLE_RX, &channel->regs->w.cr);
		channel->rx_enable = 0;
		iowrite8(CR_CMD_ASSERT_RTSN, &channel->regs->w.cr);
	}

	/*
	 * Send a packet and then disable TX to avoid failure after several send
	 * operations
	 */
	iowrite8(CR_ENABLE_TX, &channel->regs->w.cr);
	return char_copied;
}