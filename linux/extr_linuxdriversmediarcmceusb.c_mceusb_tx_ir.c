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
struct rc_dev {struct mceusb_dev* priv; } ;
struct mceusb_dev {unsigned char tx_mask; } ;

/* Variables and functions */
 int EINVAL ; 
 int MCE_CMDBUF_SIZE ; 
 unsigned char MCE_CMD_PORT_IR ; 
 unsigned char MCE_CMD_SETIRTXPORTS ; 
 int MCE_CODE_LENGTH ; 
 unsigned char MCE_IRDATA_HEADER ; 
 unsigned char MCE_IRDATA_TRAILER ; 
 unsigned int MCE_MAX_PULSE_LENGTH ; 
 unsigned int MCE_PULSE_BIT ; 
 unsigned int MCE_TIME_UNIT ; 
 int /*<<< orphan*/  mce_async_out (struct mceusb_dev*,unsigned char*,int) ; 

__attribute__((used)) static int mceusb_tx_ir(struct rc_dev *dev, unsigned *txbuf, unsigned count)
{
	struct mceusb_dev *ir = dev->priv;
	int i, length, ret = 0;
	int cmdcount = 0;
	unsigned char cmdbuf[MCE_CMDBUF_SIZE];

	/* MCE tx init header */
	cmdbuf[cmdcount++] = MCE_CMD_PORT_IR;
	cmdbuf[cmdcount++] = MCE_CMD_SETIRTXPORTS;
	cmdbuf[cmdcount++] = ir->tx_mask;

	/* Send the set TX ports command */
	mce_async_out(ir, cmdbuf, cmdcount);
	cmdcount = 0;

	/* Generate mce packet data */
	for (i = 0; (i < count) && (cmdcount < MCE_CMDBUF_SIZE); i++) {
		txbuf[i] = txbuf[i] / MCE_TIME_UNIT;

		do { /* loop to support long pulses/spaces > 127*50us=6.35ms */

			/* Insert mce packet header every 4th entry */
			if ((cmdcount < MCE_CMDBUF_SIZE) &&
			    (cmdcount % MCE_CODE_LENGTH) == 0)
				cmdbuf[cmdcount++] = MCE_IRDATA_HEADER;

			/* Insert mce packet data */
			if (cmdcount < MCE_CMDBUF_SIZE)
				cmdbuf[cmdcount++] =
					(txbuf[i] < MCE_PULSE_BIT ?
					 txbuf[i] : MCE_MAX_PULSE_LENGTH) |
					 (i & 1 ? 0x00 : MCE_PULSE_BIT);
			else {
				ret = -EINVAL;
				goto out;
			}

		} while ((txbuf[i] > MCE_MAX_PULSE_LENGTH) &&
			 (txbuf[i] -= MCE_MAX_PULSE_LENGTH));
	}

	/* Check if we have room for the empty packet at the end */
	if (cmdcount >= MCE_CMDBUF_SIZE) {
		ret = -EINVAL;
		goto out;
	}

	/* Fix packet length in last header */
	length = cmdcount % MCE_CODE_LENGTH;
	cmdbuf[cmdcount - length] -= MCE_CODE_LENGTH - length;

	/* All mce commands end with an empty packet (0x80) */
	cmdbuf[cmdcount++] = MCE_IRDATA_TRAILER;

	/* Transmit the command to the mce device */
	mce_async_out(ir, cmdbuf, cmdcount);

out:
	return ret ? ret : count;
}