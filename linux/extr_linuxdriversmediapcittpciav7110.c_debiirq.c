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
typedef  int u8 ;
struct TYPE_4__ {int /*<<< orphan*/  recording; } ;
struct av7110 {int debitype; int* debi_virt; int debilen; int /*<<< orphan*/  debilock; int /*<<< orphan*/  ci_rbuffer; TYPE_1__* ci_slot; int /*<<< orphan*/ * handle2filter; int /*<<< orphan*/ * p2t; TYPE_2__ demux; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  s8 ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_ClearMailBox (struct av7110*) ; 
 int CA_CI_MODULE_PRESENT ; 
 int CA_CI_MODULE_READY ; 
 int /*<<< orphan*/  CI_handle (struct av7110*,int*,int) ; 
#define  DATA_BMP_LOAD 138 
#define  DATA_CI_GET 137 
#define  DATA_CI_PUT 136 
#define  DATA_COMMON_INTERFACE 135 
#define  DATA_DEBUG_MESSAGE 134 
#define  DATA_FSECTION 133 
#define  DATA_IPMPE 132 
#define  DATA_MPEG_PLAY 131 
#define  DATA_PES_RECORD 130 
#define  DATA_PIPING 129 
#define  DATA_TS_RECORD 128 
 int /*<<< orphan*/  DEBINOSWAP ; 
 int /*<<< orphan*/  DvbDmxFilterCallback (int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct av7110*) ; 
 int /*<<< orphan*/  PSR ; 
 unsigned int RX_BUFF ; 
 int /*<<< orphan*/  Reserved_SIZE ; 
 int /*<<< orphan*/  SSR ; 
 unsigned int TX_BUFF ; 
 int /*<<< orphan*/  av7110_record_cb (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  ci_get_data (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 int /*<<< orphan*/  dvb_dmx_swfilter_packets (TYPE_2__*,int const*,int) ; 
 int /*<<< orphan*/  iwdebi (struct av7110*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  print_time (char*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  saa7146_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void debiirq(unsigned long cookie)
{
	struct av7110 *av7110 = (struct av7110 *)cookie;
	int type = av7110->debitype;
	int handle = (type >> 8) & 0x1f;
	unsigned int xfer = 0;

	print_time("debi");
	dprintk(4, "type 0x%04x\n", type);

	if (type == -1) {
		printk("DEBI irq oops @ %ld, psr:0x%08x, ssr:0x%08x\n",
		       jiffies, saa7146_read(av7110->dev, PSR),
		       saa7146_read(av7110->dev, SSR));
		goto debi_done;
	}
	av7110->debitype = -1;

	switch (type & 0xff) {

	case DATA_TS_RECORD:
		dvb_dmx_swfilter_packets(&av7110->demux,
					 (const u8 *) av7110->debi_virt,
					 av7110->debilen / 188);
		xfer = RX_BUFF;
		break;

	case DATA_PES_RECORD:
		if (av7110->demux.recording)
			av7110_record_cb(&av7110->p2t[handle],
					 (u8 *) av7110->debi_virt,
					 av7110->debilen);
		xfer = RX_BUFF;
		break;

	case DATA_IPMPE:
	case DATA_FSECTION:
	case DATA_PIPING:
		if (av7110->handle2filter[handle])
			DvbDmxFilterCallback((u8 *)av7110->debi_virt,
					     av7110->debilen, NULL, 0,
					     av7110->handle2filter[handle],
					     av7110);
		xfer = RX_BUFF;
		break;

	case DATA_CI_GET:
	{
		u8 *data = av7110->debi_virt;

		if ((data[0] < 2) && data[2] == 0xff) {
			int flags = 0;
			if (data[5] > 0)
				flags |= CA_CI_MODULE_PRESENT;
			if (data[5] > 5)
				flags |= CA_CI_MODULE_READY;
			av7110->ci_slot[data[0]].flags = flags;
		} else
			ci_get_data(&av7110->ci_rbuffer,
				    av7110->debi_virt,
				    av7110->debilen);
		xfer = RX_BUFF;
		break;
	}

	case DATA_COMMON_INTERFACE:
		CI_handle(av7110, (u8 *)av7110->debi_virt, av7110->debilen);
		xfer = RX_BUFF;
		break;

	case DATA_DEBUG_MESSAGE:
		((s8*)av7110->debi_virt)[Reserved_SIZE - 1] = 0;
		printk("%s\n", (s8 *) av7110->debi_virt);
		xfer = RX_BUFF;
		break;

	case DATA_CI_PUT:
		dprintk(4, "debi DATA_CI_PUT\n");
		xfer = TX_BUFF;
		break;
	case DATA_MPEG_PLAY:
		dprintk(4, "debi DATA_MPEG_PLAY\n");
		xfer = TX_BUFF;
		break;
	case DATA_BMP_LOAD:
		dprintk(4, "debi DATA_BMP_LOAD\n");
		xfer = TX_BUFF;
		break;
	default:
		break;
	}
debi_done:
	spin_lock(&av7110->debilock);
	if (xfer)
		iwdebi(av7110, DEBINOSWAP, xfer, 0, 2);
	ARM_ClearMailBox(av7110);
	spin_unlock(&av7110->debilock);
}