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
typedef  int /*<<< orphan*/  u_char ;
struct bzfifo {TYPE_1__* za; } ;
struct bchannel {int dropcnt; int /*<<< orphan*/  rx_skb; int /*<<< orphan*/  nr; int /*<<< orphan*/  Flags; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  z1; } ;

/* Variables and functions */
 int B_FIFO_SIZE ; 
 int B_SUB_VAL ; 
 int /*<<< orphan*/  FLG_RX_OFF ; 
 size_t MAX_B_FRAMES ; 
 int bchannel_get_rxbuf (struct bchannel*,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  recv_Bchannel (struct bchannel*,int,int) ; 
 int /*<<< orphan*/ * skb_put (int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hfcpci_empty_fifo_trans(struct bchannel *bch, struct bzfifo *rxbz,
			struct bzfifo *txbz, u_char *bdata)
{
	__le16	*z1r, *z2r, *z1t, *z2t;
	int	new_z2, fcnt_rx, fcnt_tx, maxlen;
	u_char	*ptr, *ptr1;

	z1r = &rxbz->za[MAX_B_FRAMES].z1;	/* pointer to z reg */
	z2r = z1r + 1;
	z1t = &txbz->za[MAX_B_FRAMES].z1;
	z2t = z1t + 1;

	fcnt_rx = le16_to_cpu(*z1r) - le16_to_cpu(*z2r);
	if (!fcnt_rx)
		return;	/* no data avail */

	if (fcnt_rx <= 0)
		fcnt_rx += B_FIFO_SIZE;	/* bytes actually buffered */
	new_z2 = le16_to_cpu(*z2r) + fcnt_rx;	/* new position in fifo */
	if (new_z2 >= (B_FIFO_SIZE + B_SUB_VAL))
		new_z2 -= B_FIFO_SIZE;	/* buffer wrap */

	fcnt_tx = le16_to_cpu(*z2t) - le16_to_cpu(*z1t);
	if (fcnt_tx <= 0)
		fcnt_tx += B_FIFO_SIZE;
	/* fcnt_tx contains available bytes in tx-fifo */
	fcnt_tx = B_FIFO_SIZE - fcnt_tx;
	/* remaining bytes to send (bytes in tx-fifo) */

	if (test_bit(FLG_RX_OFF, &bch->Flags)) {
		bch->dropcnt += fcnt_rx;
		*z2r = cpu_to_le16(new_z2);
		return;
	}
	maxlen = bchannel_get_rxbuf(bch, fcnt_rx);
	if (maxlen < 0) {
		pr_warning("B%d: No bufferspace for %d bytes\n",
			   bch->nr, fcnt_rx);
	} else {
		ptr = skb_put(bch->rx_skb, fcnt_rx);
		if (le16_to_cpu(*z2r) + fcnt_rx <= B_FIFO_SIZE + B_SUB_VAL)
			maxlen = fcnt_rx;	/* complete transfer */
		else
			maxlen = B_FIFO_SIZE + B_SUB_VAL - le16_to_cpu(*z2r);
		/* maximum */

		ptr1 = bdata + (le16_to_cpu(*z2r) - B_SUB_VAL);
		/* start of data */
		memcpy(ptr, ptr1, maxlen);	/* copy data */
		fcnt_rx -= maxlen;

		if (fcnt_rx) {	/* rest remaining */
			ptr += maxlen;
			ptr1 = bdata;	/* start of buffer */
			memcpy(ptr, ptr1, fcnt_rx);	/* rest */
		}
		recv_Bchannel(bch, fcnt_tx, false); /* bch, id, !force */
	}
	*z2r = cpu_to_le16(new_z2);		/* new position */
}