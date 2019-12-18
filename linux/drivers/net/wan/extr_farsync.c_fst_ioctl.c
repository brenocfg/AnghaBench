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
struct net_device {int dummy; } ;
struct TYPE_2__ {int type; } ;
struct ifreq {TYPE_1__ ifr_settings; int /*<<< orphan*/ * ifr_data; } ;
struct fstioc_write {scalar_t__ size; scalar_t__ offset; } ;
struct fstioc_info {scalar_t__ size; scalar_t__ offset; } ;
struct fst_port_info {int /*<<< orphan*/  mode; struct fst_card_info* card; } ;
struct fst_card_info {int /*<<< orphan*/  state; int /*<<< orphan*/  card_no; int /*<<< orphan*/  card_lock; scalar_t__ mem; } ;
typedef  int /*<<< orphan*/  info ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int /*<<< orphan*/  DBG_IOCTL ; 
 int EFAULT ; 
 int EINVAL ; 
 int EIO ; 
 int ENXIO ; 
 int EPERM ; 
#define  FSTCPURELEASE 143 
#define  FSTCPURESET 142 
#define  FSTGETCONF 141 
#define  FSTSETCONF 140 
#define  FSTWRITE 139 
 int /*<<< orphan*/  FST_DOWNLOAD ; 
 int /*<<< orphan*/  FST_GEN_HDLC ; 
 scalar_t__ FST_MEMSIZE ; 
 int /*<<< orphan*/  FST_RAW ; 
 int /*<<< orphan*/  FST_RESET ; 
 int /*<<< orphan*/  FST_RUNNING ; 
 int /*<<< orphan*/  FST_STARTING ; 
 int /*<<< orphan*/  FST_WRB (struct fst_card_info*,int /*<<< orphan*/ ,int) ; 
#define  IF_GET_IFACE 138 
#define  IF_GET_PROTO 137 
#define  IF_IFACE_E1 136 
#define  IF_IFACE_SYNC_SERIAL 135 
#define  IF_IFACE_T1 134 
#define  IF_IFACE_V24 133 
#define  IF_IFACE_V35 132 
#define  IF_IFACE_X21 131 
#define  IF_IFACE_X21D 130 
#define  IF_PROTO_RAW 129 
 int /*<<< orphan*/  IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
#define  SIOCWANDEV 128 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_started_ok (struct fst_card_info*) ; 
 int /*<<< orphan*/  copy_from_user (struct fstioc_write*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  copy_to_user (int /*<<< orphan*/ *,struct fstioc_write*,int) ; 
 int /*<<< orphan*/  dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 struct fst_port_info* dev_to_port (struct net_device*) ; 
 int /*<<< orphan*/  fst_cpurelease (struct fst_card_info*) ; 
 int /*<<< orphan*/  fst_cpureset (struct fst_card_info*) ; 
 int /*<<< orphan*/  fst_enable_intr (struct fst_card_info*) ; 
 int fst_get_iface (struct fst_card_info*,struct fst_port_info*,struct ifreq*) ; 
 int fst_set_iface (struct fst_card_info*,struct fst_port_info*,struct ifreq*) ; 
 int /*<<< orphan*/  gather_conf_info (struct fst_card_info*,struct fst_port_info*,struct fstioc_write*) ; 
 int hdlc_ioctl (struct net_device*,struct ifreq*,int) ; 
 int /*<<< orphan*/  interruptHandshake ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  memcpy_toio (scalar_t__,void*,scalar_t__) ; 
 void* memdup_user (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int set_conf_from_info (struct fst_card_info*,struct fst_port_info*,struct fstioc_write*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
fst_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct fst_card_info *card;
	struct fst_port_info *port;
	struct fstioc_write wrthdr;
	struct fstioc_info info;
	unsigned long flags;
	void *buf;

	dbg(DBG_IOCTL, "ioctl: %x, %p\n", cmd, ifr->ifr_data);

	port = dev_to_port(dev);
	card = port->card;

	if (!capable(CAP_NET_ADMIN))
		return -EPERM;

	switch (cmd) {
	case FSTCPURESET:
		fst_cpureset(card);
		card->state = FST_RESET;
		return 0;

	case FSTCPURELEASE:
		fst_cpurelease(card);
		card->state = FST_STARTING;
		return 0;

	case FSTWRITE:		/* Code write (download) */

		/* First copy in the header with the length and offset of data
		 * to write
		 */
		if (ifr->ifr_data == NULL) {
			return -EINVAL;
		}
		if (copy_from_user(&wrthdr, ifr->ifr_data,
				   sizeof (struct fstioc_write))) {
			return -EFAULT;
		}

		/* Sanity check the parameters. We don't support partial writes
		 * when going over the top
		 */
		if (wrthdr.size > FST_MEMSIZE || wrthdr.offset > FST_MEMSIZE ||
		    wrthdr.size + wrthdr.offset > FST_MEMSIZE) {
			return -ENXIO;
		}

		/* Now copy the data to the card. */

		buf = memdup_user(ifr->ifr_data + sizeof(struct fstioc_write),
				  wrthdr.size);
		if (IS_ERR(buf))
			return PTR_ERR(buf);

		memcpy_toio(card->mem + wrthdr.offset, buf, wrthdr.size);
		kfree(buf);

		/* Writes to the memory of a card in the reset state constitute
		 * a download
		 */
		if (card->state == FST_RESET) {
			card->state = FST_DOWNLOAD;
		}
		return 0;

	case FSTGETCONF:

		/* If card has just been started check the shared memory config
		 * version and marker
		 */
		if (card->state == FST_STARTING) {
			check_started_ok(card);

			/* If everything checked out enable card interrupts */
			if (card->state == FST_RUNNING) {
				spin_lock_irqsave(&card->card_lock, flags);
				fst_enable_intr(card);
				FST_WRB(card, interruptHandshake, 0xEE);
				spin_unlock_irqrestore(&card->card_lock, flags);
			}
		}

		if (ifr->ifr_data == NULL) {
			return -EINVAL;
		}

		gather_conf_info(card, port, &info);

		if (copy_to_user(ifr->ifr_data, &info, sizeof (info))) {
			return -EFAULT;
		}
		return 0;

	case FSTSETCONF:

		/*
		 * Most of the settings have been moved to the generic ioctls
		 * this just covers debug and board ident now
		 */

		if (card->state != FST_RUNNING) {
			pr_err("Attempt to configure card %d in non-running state (%d)\n",
			       card->card_no, card->state);
			return -EIO;
		}
		if (copy_from_user(&info, ifr->ifr_data, sizeof (info))) {
			return -EFAULT;
		}

		return set_conf_from_info(card, port, &info);

	case SIOCWANDEV:
		switch (ifr->ifr_settings.type) {
		case IF_GET_IFACE:
			return fst_get_iface(card, port, ifr);

		case IF_IFACE_SYNC_SERIAL:
		case IF_IFACE_V35:
		case IF_IFACE_V24:
		case IF_IFACE_X21:
		case IF_IFACE_X21D:
		case IF_IFACE_T1:
		case IF_IFACE_E1:
			return fst_set_iface(card, port, ifr);

		case IF_PROTO_RAW:
			port->mode = FST_RAW;
			return 0;

		case IF_GET_PROTO:
			if (port->mode == FST_RAW) {
				ifr->ifr_settings.type = IF_PROTO_RAW;
				return 0;
			}
			return hdlc_ioctl(dev, ifr, cmd);

		default:
			port->mode = FST_GEN_HDLC;
			dbg(DBG_IOCTL, "Passing this type to hdlc %x\n",
			    ifr->ifr_settings.type);
			return hdlc_ioctl(dev, ifr, cmd);
		}

	default:
		/* Not one of ours. Pass through to HDLC package */
		return hdlc_ioctl(dev, ifr, cmd);
	}
}