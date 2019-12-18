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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct frhdr {int /*<<< orphan*/  PID; int /*<<< orphan*/  OUI; int /*<<< orphan*/  NLPID; int /*<<< orphan*/  pad; int /*<<< orphan*/  IP_NLPID; int /*<<< orphan*/  control; } ;
typedef  int /*<<< orphan*/  hdr ;

/* Variables and functions */
#define  ETH_P_IP 128 
 int /*<<< orphan*/  FRAD_I_UI ; 
 int /*<<< orphan*/  FRAD_P_IP ; 
 int /*<<< orphan*/  FRAD_P_PADDING ; 
 int /*<<< orphan*/  FRAD_P_SNAP ; 
 int /*<<< orphan*/  htons (unsigned short) ; 
 int /*<<< orphan*/  memcpy (char*,struct frhdr*,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* skb_push (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static int dlci_header(struct sk_buff *skb, struct net_device *dev, 
		       unsigned short type, const void *daddr,
		       const void *saddr, unsigned len)
{
	struct frhdr		hdr;
	unsigned int		hlen;
	char			*dest;

	hdr.control = FRAD_I_UI;
	switch (type)
	{
		case ETH_P_IP:
			hdr.IP_NLPID = FRAD_P_IP;
			hlen = sizeof(hdr.control) + sizeof(hdr.IP_NLPID);
			break;

		/* feel free to add other types, if necessary */

		default:
			hdr.pad = FRAD_P_PADDING;
			hdr.NLPID = FRAD_P_SNAP;
			memset(hdr.OUI, 0, sizeof(hdr.OUI));
			hdr.PID = htons(type);
			hlen = sizeof(hdr);
			break;
	}

	dest = skb_push(skb, hlen);
	if (!dest)
		return 0;

	memcpy(dest, &hdr, hlen);

	return hlen;
}