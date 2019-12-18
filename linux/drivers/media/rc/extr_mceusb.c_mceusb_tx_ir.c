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
typedef  int u8 ;
struct rc_dev {struct mceusb_dev* priv; } ;
struct mceusb_dev {int tx_mask; } ;
typedef  int /*<<< orphan*/  cmdbuf ;

/* Variables and functions */
 int MCE_CMD_PORT_IR ; 
 int MCE_CMD_SETIRTXPORTS ; 
 int MCE_IRBUF_SIZE ; 
 int MCE_IRDATA_HEADER ; 
 int MCE_IRDATA_TRAILER ; 
 unsigned int MCE_MAX_PULSE_LENGTH ; 
 int MCE_PACKET_SIZE ; 
 int MCE_PULSE_BIT ; 
 unsigned int MCE_TIME_UNIT ; 
 int /*<<< orphan*/  mce_command_out (struct mceusb_dev*,int*,int) ; 
 int mce_write (struct mceusb_dev*,int*,int) ; 

__attribute__((used)) static int mceusb_tx_ir(struct rc_dev *dev, unsigned *txbuf, unsigned count)
{
	struct mceusb_dev *ir = dev->priv;
	u8 cmdbuf[3] = { MCE_CMD_PORT_IR, MCE_CMD_SETIRTXPORTS, 0x00 };
	u8 irbuf[MCE_IRBUF_SIZE];
	int ircount = 0;
	unsigned int irsample;
	int i, length, ret;

	/* Send the set TX ports command */
	cmdbuf[2] = ir->tx_mask;
	mce_command_out(ir, cmdbuf, sizeof(cmdbuf));

	/* Generate mce IR data packet */
	for (i = 0; i < count; i++) {
		irsample = txbuf[i] / MCE_TIME_UNIT;

		/* loop to support long pulses/spaces > 6350us (127*50us) */
		while (irsample > 0) {
			/* Insert IR header every 30th entry */
			if (ircount % MCE_PACKET_SIZE == 0) {
				/* Room for IR header and one IR sample? */
				if (ircount >= MCE_IRBUF_SIZE - 1) {
					/* Send near full buffer */
					ret = mce_write(ir, irbuf, ircount);
					if (ret < 0)
						return ret;
					ircount = 0;
				}
				irbuf[ircount++] = MCE_IRDATA_HEADER;
			}

			/* Insert IR sample */
			if (irsample <= MCE_MAX_PULSE_LENGTH) {
				irbuf[ircount] = irsample;
				irsample = 0;
			} else {
				irbuf[ircount] = MCE_MAX_PULSE_LENGTH;
				irsample -= MCE_MAX_PULSE_LENGTH;
			}
			/*
			 * Even i = IR pulse
			 * Odd  i = IR space
			 */
			irbuf[ircount] |= (i & 1 ? 0 : MCE_PULSE_BIT);
			ircount++;

			/* IR buffer full? */
			if (ircount >= MCE_IRBUF_SIZE) {
				/* Fix packet length in last header */
				length = ircount % MCE_PACKET_SIZE;
				if (length > 0)
					irbuf[ircount - length] -=
						MCE_PACKET_SIZE - length;
				/* Send full buffer */
				ret = mce_write(ir, irbuf, ircount);
				if (ret < 0)
					return ret;
				ircount = 0;
			}
		}
	} /* after for loop, 0 <= ircount < MCE_IRBUF_SIZE */

	/* Fix packet length in last header */
	length = ircount % MCE_PACKET_SIZE;
	if (length > 0)
		irbuf[ircount - length] -= MCE_PACKET_SIZE - length;

	/* Append IR trailer (0x80) to final partial (or empty) IR buffer */
	irbuf[ircount++] = MCE_IRDATA_TRAILER;

	/* Send final buffer */
	ret = mce_write(ir, irbuf, ircount);
	if (ret < 0)
		return ret;

	return count;
}