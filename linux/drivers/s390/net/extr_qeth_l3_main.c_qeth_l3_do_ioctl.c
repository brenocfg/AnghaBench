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
struct qeth_card {int dummy; } ;
struct qeth_arp_cache_entry {int dummy; } ;
struct net_device {struct qeth_card* ml_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifru_data; int /*<<< orphan*/  ifru_ivalue; } ;
struct ifreq {int /*<<< orphan*/  ifr_data; TYPE_1__ ifr_ifru; } ;
typedef  enum qeth_arp_process_subcmds { ____Placeholder_qeth_arp_process_subcmds } qeth_arp_process_subcmds ;
typedef  int /*<<< orphan*/  arp_entry ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EFAULT ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int IPA_CMD_ASS_ARP_ADD_ENTRY ; 
 int IPA_CMD_ASS_ARP_REMOVE_ENTRY ; 
#define  SIOC_QETH_ARP_ADD_ENTRY 132 
#define  SIOC_QETH_ARP_FLUSH_CACHE 131 
#define  SIOC_QETH_ARP_QUERY_INFO 130 
#define  SIOC_QETH_ARP_REMOVE_ENTRY 129 
#define  SIOC_QETH_ARP_SET_NO_ENTRIES 128 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_from_user (struct qeth_arp_cache_entry*,int /*<<< orphan*/ ,int) ; 
 int qeth_l3_arp_flush_cache (struct qeth_card*) ; 
 int qeth_l3_arp_modify_entry (struct qeth_card*,struct qeth_arp_cache_entry*,int) ; 
 int qeth_l3_arp_query (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int qeth_l3_arp_set_no_entries (struct qeth_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_l3_do_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct qeth_card *card = dev->ml_priv;
	struct qeth_arp_cache_entry arp_entry;
	enum qeth_arp_process_subcmds arp_cmd;
	int rc = 0;

	switch (cmd) {
	case SIOC_QETH_ARP_SET_NO_ENTRIES:
		if (!capable(CAP_NET_ADMIN)) {
			rc = -EPERM;
			break;
		}
		rc = qeth_l3_arp_set_no_entries(card, rq->ifr_ifru.ifru_ivalue);
		break;
	case SIOC_QETH_ARP_QUERY_INFO:
		if (!capable(CAP_NET_ADMIN)) {
			rc = -EPERM;
			break;
		}
		rc = qeth_l3_arp_query(card, rq->ifr_ifru.ifru_data);
		break;
	case SIOC_QETH_ARP_ADD_ENTRY:
	case SIOC_QETH_ARP_REMOVE_ENTRY:
		if (!capable(CAP_NET_ADMIN))
			return -EPERM;
		if (copy_from_user(&arp_entry, rq->ifr_data, sizeof(arp_entry)))
			return -EFAULT;

		arp_cmd = (cmd == SIOC_QETH_ARP_ADD_ENTRY) ?
				IPA_CMD_ASS_ARP_ADD_ENTRY :
				IPA_CMD_ASS_ARP_REMOVE_ENTRY;
		return qeth_l3_arp_modify_entry(card, &arp_entry, arp_cmd);
	case SIOC_QETH_ARP_FLUSH_CACHE:
		if (!capable(CAP_NET_ADMIN)) {
			rc = -EPERM;
			break;
		}
		rc = qeth_l3_arp_flush_cache(card);
		break;
	default:
		rc = -EOPNOTSUPP;
	}
	return rc;
}