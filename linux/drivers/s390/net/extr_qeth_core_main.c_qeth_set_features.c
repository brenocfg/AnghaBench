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
struct qeth_card {int dummy; } ;
struct net_device {int features; struct qeth_card* ml_priv; } ;
typedef  int netdev_features_t ;
typedef  int /*<<< orphan*/  features ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IPA_OUTBOUND_CHECKSUM ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 int /*<<< orphan*/  QETH_CARD_HEX (struct qeth_card*,int,int*,int) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_PROT_IPV4 ; 
 int /*<<< orphan*/  QETH_PROT_IPV6 ; 
 int qeth_set_ipa_csum (struct qeth_card*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qeth_set_ipa_rx_csum (struct qeth_card*,int) ; 
 int qeth_set_ipa_tso (struct qeth_card*,int,int /*<<< orphan*/ ) ; 

int qeth_set_features(struct net_device *dev, netdev_features_t features)
{
	struct qeth_card *card = dev->ml_priv;
	netdev_features_t changed = dev->features ^ features;
	int rc = 0;

	QETH_CARD_TEXT(card, 2, "setfeat");
	QETH_CARD_HEX(card, 2, &features, sizeof(features));

	if ((changed & NETIF_F_IP_CSUM)) {
		rc = qeth_set_ipa_csum(card, features & NETIF_F_IP_CSUM,
				       IPA_OUTBOUND_CHECKSUM, QETH_PROT_IPV4);
		if (rc)
			changed ^= NETIF_F_IP_CSUM;
	}
	if (changed & NETIF_F_IPV6_CSUM) {
		rc = qeth_set_ipa_csum(card, features & NETIF_F_IPV6_CSUM,
				       IPA_OUTBOUND_CHECKSUM, QETH_PROT_IPV6);
		if (rc)
			changed ^= NETIF_F_IPV6_CSUM;
	}
	if (changed & NETIF_F_RXCSUM) {
		rc = qeth_set_ipa_rx_csum(card, features & NETIF_F_RXCSUM);
		if (rc)
			changed ^= NETIF_F_RXCSUM;
	}
	if (changed & NETIF_F_TSO) {
		rc = qeth_set_ipa_tso(card, features & NETIF_F_TSO,
				      QETH_PROT_IPV4);
		if (rc)
			changed ^= NETIF_F_TSO;
	}
	if (changed & NETIF_F_TSO6) {
		rc = qeth_set_ipa_tso(card, features & NETIF_F_TSO6,
				      QETH_PROT_IPV6);
		if (rc)
			changed ^= NETIF_F_TSO6;
	}

	/* everything changed successfully? */
	if ((dev->features ^ features) == changed)
		return 0;
	/* something went wrong. save changed features and return error */
	dev->features ^= changed;
	return -EIO;
}