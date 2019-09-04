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
struct ptsreq {unsigned long protocol; int /*<<< orphan*/  pts3; int /*<<< orphan*/  pts2; int /*<<< orphan*/  pts1; scalar_t__ flags; } ;
struct cm4000_dev {int* pts; int proto; int ta1; int flags1; int baudv; int /*<<< orphan*/  flags; TYPE_2__* p_dev; } ;
typedef  int ssize_t ;
struct TYPE_4__ {TYPE_1__** resource; } ;
struct TYPE_3__ {unsigned int start; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGP (int,struct cm4000_dev*,char*,...) ; 
 int EIO ; 
 int /*<<< orphan*/  IS_INVREV ; 
 int /*<<< orphan*/  REG_BUF_ADDR (unsigned int) ; 
 int /*<<< orphan*/  REG_BUF_DATA (unsigned int) ; 
 int /*<<< orphan*/  REG_FLAGS0 (unsigned int) ; 
 int /*<<< orphan*/  REG_FLAGS1 (unsigned int) ; 
 int /*<<< orphan*/  REG_NUM_SEND (unsigned int) ; 
 void* calc_baudv (int) ; 
 int** fi_di_table ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_read_num_rec_bytes (unsigned int,unsigned short*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  set_cardparameter (struct cm4000_dev*) ; 
 int /*<<< orphan*/  str_invert_revert (int*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xoutb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_protocol(struct cm4000_dev *dev, struct ptsreq *ptsreq)
{

	unsigned long tmp, i;
	unsigned short num_bytes_read;
	unsigned char pts_reply[4];
	ssize_t rc;
	unsigned int iobase = dev->p_dev->resource[0]->start;

	rc = 0;

	DEBUGP(3, dev, "-> set_protocol\n");
	DEBUGP(5, dev, "ptsreq->Protocol = 0x%.8x, ptsreq->Flags=0x%.8x, "
		 "ptsreq->pts1=0x%.2x, ptsreq->pts2=0x%.2x, "
		 "ptsreq->pts3=0x%.2x\n", (unsigned int)ptsreq->protocol,
		 (unsigned int)ptsreq->flags, ptsreq->pts1, ptsreq->pts2,
		 ptsreq->pts3);

	/* Fill PTS structure */
	dev->pts[0] = 0xff;
	dev->pts[1] = 0x00;
	tmp = ptsreq->protocol;
	while ((tmp = (tmp >> 1)) > 0)
		dev->pts[1]++;
	dev->proto = dev->pts[1];	/* Set new protocol */
	dev->pts[1] = (0x01 << 4) | (dev->pts[1]);

	/* Correct Fi/Di according to CM4000 Fi/Di table */
	DEBUGP(5, dev, "Ta(1) from ATR is 0x%.2x\n", dev->ta1);
	/* set Fi/Di according to ATR TA(1) */
	dev->pts[2] = fi_di_table[dev->ta1 & 0x0F][(dev->ta1 >> 4) & 0x0F];

	/* Calculate PCK character */
	dev->pts[3] = dev->pts[0] ^ dev->pts[1] ^ dev->pts[2];

	DEBUGP(5, dev, "pts0=%.2x, pts1=%.2x, pts2=%.2x, pts3=%.2x\n",
	       dev->pts[0], dev->pts[1], dev->pts[2], dev->pts[3]);

	/* check card convention */
	if (test_bit(IS_INVREV, &dev->flags))
		str_invert_revert(dev->pts, 4);

	/* reset SM */
	xoutb(0x80, REG_FLAGS0(iobase));

	/* Enable access to the message buffer */
	DEBUGP(5, dev, "Enable access to the messages buffer\n");
	dev->flags1 = 0x20	/* T_Active */
	    | (test_bit(IS_INVREV, &dev->flags) ? 0x02 : 0x00) /* inv parity */
	    | ((dev->baudv >> 8) & 0x01);	/* MSB-baud */
	xoutb(dev->flags1, REG_FLAGS1(iobase));

	DEBUGP(5, dev, "Enable message buffer -> flags1 = 0x%.2x\n",
	       dev->flags1);

	/* write challenge to the buffer */
	DEBUGP(5, dev, "Write challenge to buffer: ");
	for (i = 0; i < 4; i++) {
		xoutb(i, REG_BUF_ADDR(iobase));
		xoutb(dev->pts[i], REG_BUF_DATA(iobase));	/* buf data */
#ifdef CM4000_DEBUG
		pr_debug("0x%.2x ", dev->pts[i]);
	}
	pr_debug("\n");
#else
	}
#endif

	/* set number of bytes to write */
	DEBUGP(5, dev, "Set number of bytes to write\n");
	xoutb(0x04, REG_NUM_SEND(iobase));

	/* Trigger CARDMAN CONTROLLER */
	xoutb(0x50, REG_FLAGS0(iobase));

	/* Monitor progress */
	/* wait for xmit done */
	DEBUGP(5, dev, "Waiting for NumRecBytes getting valid\n");

	for (i = 0; i < 100; i++) {
		if (inb(REG_FLAGS0(iobase)) & 0x08) {
			DEBUGP(5, dev, "NumRecBytes is valid\n");
			break;
		}
		mdelay(10);
	}
	if (i == 100) {
		DEBUGP(5, dev, "Timeout waiting for NumRecBytes getting "
		       "valid\n");
		rc = -EIO;
		goto exit_setprotocol;
	}

	DEBUGP(5, dev, "Reading NumRecBytes\n");
	for (i = 0; i < 100; i++) {
		io_read_num_rec_bytes(iobase, &num_bytes_read);
		if (num_bytes_read >= 4) {
			DEBUGP(2, dev, "NumRecBytes = %i\n", num_bytes_read);
			break;
		}
		mdelay(10);
	}

	/* check whether it is a short PTS reply? */
	if (num_bytes_read == 3)
		i = 0;

	if (i == 100) {
		DEBUGP(5, dev, "Timeout reading num_bytes_read\n");
		rc = -EIO;
		goto exit_setprotocol;
	}

	DEBUGP(5, dev, "Reset the CARDMAN CONTROLLER\n");
	xoutb(0x80, REG_FLAGS0(iobase));

	/* Read PPS reply */
	DEBUGP(5, dev, "Read PPS reply\n");
	for (i = 0; i < num_bytes_read; i++) {
		xoutb(i, REG_BUF_ADDR(iobase));
		pts_reply[i] = inb(REG_BUF_DATA(iobase));
	}

#ifdef CM4000_DEBUG
	DEBUGP(2, dev, "PTSreply: ");
	for (i = 0; i < num_bytes_read; i++) {
		pr_debug("0x%.2x ", pts_reply[i]);
	}
	pr_debug("\n");
#endif	/* CM4000_DEBUG */

	DEBUGP(5, dev, "Clear Tactive in Flags1\n");
	xoutb(0x20, REG_FLAGS1(iobase));

	/* Compare ptsreq and ptsreply */
	if ((dev->pts[0] == pts_reply[0]) &&
	    (dev->pts[1] == pts_reply[1]) &&
	    (dev->pts[2] == pts_reply[2]) && (dev->pts[3] == pts_reply[3])) {
		/* setcardparameter according to PPS */
		dev->baudv = calc_baudv(dev->pts[2]);
		set_cardparameter(dev);
	} else if ((dev->pts[0] == pts_reply[0]) &&
		   ((dev->pts[1] & 0xef) == pts_reply[1]) &&
		   ((pts_reply[0] ^ pts_reply[1]) == pts_reply[2])) {
		/* short PTS reply, set card parameter to default values */
		dev->baudv = calc_baudv(0x11);
		set_cardparameter(dev);
	} else
		rc = -EIO;

exit_setprotocol:
	DEBUGP(3, dev, "<- set_protocol\n");
	return rc;
}