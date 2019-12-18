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
struct si470x_device {int* registers; size_t wr_index; int buf_size; int rd_index; int /*<<< orphan*/  read_queue; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  completion; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 size_t RDSA ; 
 size_t RDSB ; 
 size_t RDSC ; 
 size_t RDSD ; 
 unsigned char RDS_REGISTER_NUM ; 
 size_t READCHAN ; 
 int READCHAN_BLERB ; 
 int READCHAN_BLERC ; 
 int READCHAN_BLERD ; 
 size_t STATUSRSSI ; 
 int STATUSRSSI_BLERA ; 
 int STATUSRSSI_RDSR ; 
 int STATUSRSSI_STC ; 
 size_t SYSCONFIG1 ; 
 int SYSCONFIG1_RDS ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 unsigned short max_rds_errors ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char**,int) ; 
 int /*<<< orphan*/  put_unaligned_le16 (unsigned short,unsigned char**) ; 
 int si470x_get_register (struct si470x_device*,size_t) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t si470x_i2c_interrupt(int irq, void *dev_id)
{
	struct si470x_device *radio = dev_id;
	unsigned char regnr;
	unsigned char blocknum;
	unsigned short bler; /* rds block errors */
	unsigned short rds;
	unsigned char tmpbuf[3];
	int retval = 0;

	/* check Seek/Tune Complete */
	retval = si470x_get_register(radio, STATUSRSSI);
	if (retval < 0)
		goto end;

	if (radio->registers[STATUSRSSI] & STATUSRSSI_STC)
		complete(&radio->completion);

	/* safety checks */
	if ((radio->registers[SYSCONFIG1] & SYSCONFIG1_RDS) == 0)
		goto end;

	/* Update RDS registers */
	for (regnr = 1; regnr < RDS_REGISTER_NUM; regnr++) {
		retval = si470x_get_register(radio, STATUSRSSI + regnr);
		if (retval < 0)
			goto end;
	}

	/* get rds blocks */
	if ((radio->registers[STATUSRSSI] & STATUSRSSI_RDSR) == 0)
		/* No RDS group ready, better luck next time */
		goto end;

	for (blocknum = 0; blocknum < 4; blocknum++) {
		switch (blocknum) {
		default:
			bler = (radio->registers[STATUSRSSI] &
					STATUSRSSI_BLERA) >> 9;
			rds = radio->registers[RDSA];
			break;
		case 1:
			bler = (radio->registers[READCHAN] &
					READCHAN_BLERB) >> 14;
			rds = radio->registers[RDSB];
			break;
		case 2:
			bler = (radio->registers[READCHAN] &
					READCHAN_BLERC) >> 12;
			rds = radio->registers[RDSC];
			break;
		case 3:
			bler = (radio->registers[READCHAN] &
					READCHAN_BLERD) >> 10;
			rds = radio->registers[RDSD];
			break;
		}

		/* Fill the V4L2 RDS buffer */
		put_unaligned_le16(rds, &tmpbuf);
		tmpbuf[2] = blocknum;		/* offset name */
		tmpbuf[2] |= blocknum << 3;	/* received offset */
		if (bler > max_rds_errors)
			tmpbuf[2] |= 0x80;	/* uncorrectable errors */
		else if (bler > 0)
			tmpbuf[2] |= 0x40;	/* corrected error(s) */

		/* copy RDS block to internal buffer */
		memcpy(&radio->buffer[radio->wr_index], &tmpbuf, 3);
		radio->wr_index += 3;

		/* wrap write pointer */
		if (radio->wr_index >= radio->buf_size)
			radio->wr_index = 0;

		/* check for overflow */
		if (radio->wr_index == radio->rd_index) {
			/* increment and wrap read pointer */
			radio->rd_index += 3;
			if (radio->rd_index >= radio->buf_size)
				radio->rd_index = 0;
		}
	}

	if (radio->wr_index != radio->rd_index)
		wake_up_interruptible(&radio->read_queue);

end:
	return IRQ_HANDLED;
}