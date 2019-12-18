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
struct sk_buff {scalar_t__ len; int priority; int /*<<< orphan*/  ip_summed; scalar_t__ data; } ;
struct brcmf_pub {int dummy; } ;
struct brcmf_proto_bcdc_header {int flags; int priority; int data_offset; } ;
struct brcmf_if {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCDC ; 
 int BCDC_FLAG_SUM_GOOD ; 
 int BCDC_FLAG_VER_MASK ; 
 int BCDC_FLAG_VER_SHIFT ; 
 int /*<<< orphan*/  BCDC_GET_IF_IDX (struct brcmf_proto_bcdc_header*) ; 
 scalar_t__ BCDC_HEADER_LEN ; 
 int BCDC_PRIORITY_MASK ; 
 int BCDC_PROTO_VER ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int EBADE ; 
 int ENODATA ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  brcmf_fws_hdrpull (struct brcmf_if*,int,struct sk_buff*) ; 
 struct brcmf_if* brcmf_get_ifp (struct brcmf_pub*,int /*<<< orphan*/ ) ; 
 scalar_t__ brcmf_ifname (struct brcmf_if*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  trace_brcmf_bcdchdr (scalar_t__) ; 

__attribute__((used)) static int
brcmf_proto_bcdc_hdrpull(struct brcmf_pub *drvr, bool do_fws,
			 struct sk_buff *pktbuf, struct brcmf_if **ifp)
{
	struct brcmf_proto_bcdc_header *h;
	struct brcmf_if *tmp_if;

	brcmf_dbg(BCDC, "Enter\n");

	/* Pop BCDC header used to convey priority for buses that don't */
	if (pktbuf->len <= BCDC_HEADER_LEN) {
		brcmf_dbg(INFO, "rx data too short (%d <= %d)\n",
			  pktbuf->len, BCDC_HEADER_LEN);
		return -EBADE;
	}

	trace_brcmf_bcdchdr(pktbuf->data);
	h = (struct brcmf_proto_bcdc_header *)(pktbuf->data);

	tmp_if = brcmf_get_ifp(drvr, BCDC_GET_IF_IDX(h));
	if (!tmp_if) {
		brcmf_dbg(INFO, "no matching ifp found\n");
		return -EBADE;
	}
	if (((h->flags & BCDC_FLAG_VER_MASK) >> BCDC_FLAG_VER_SHIFT) !=
	    BCDC_PROTO_VER) {
		bphy_err(drvr, "%s: non-BCDC packet received, flags 0x%x\n",
			 brcmf_ifname(tmp_if), h->flags);
		return -EBADE;
	}

	if (h->flags & BCDC_FLAG_SUM_GOOD) {
		brcmf_dbg(BCDC, "%s: BDC rcv, good checksum, flags 0x%x\n",
			  brcmf_ifname(tmp_if), h->flags);
		pktbuf->ip_summed = CHECKSUM_UNNECESSARY;
	}

	pktbuf->priority = h->priority & BCDC_PRIORITY_MASK;

	skb_pull(pktbuf, BCDC_HEADER_LEN);
	if (do_fws)
		brcmf_fws_hdrpull(tmp_if, h->data_offset << 2, pktbuf);
	else
		skb_pull(pktbuf, h->data_offset << 2);

	if (pktbuf->len == 0)
		return -ENODATA;

	if (ifp != NULL)
		*ifp = tmp_if;
	return 0;
}