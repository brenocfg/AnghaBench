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
typedef  int /*<<< orphan*/  tx_desc_hdr ;
struct seq_file {struct fm10k_ring* private; } ;
struct fm10k_tx_desc {int /*<<< orphan*/  flags; int /*<<< orphan*/  hdrlen; int /*<<< orphan*/  mss; int /*<<< orphan*/  vlan; int /*<<< orphan*/  buflen; int /*<<< orphan*/  buffer_addr; } ;
struct fm10k_ring {int /*<<< orphan*/  desc; } ;
typedef  int loff_t ;

/* Variables and functions */
 struct fm10k_tx_desc* FM10K_TX_DESC (struct fm10k_ring*,int) ; 
 int /*<<< orphan*/  fm10k_dbg_desc_break (struct seq_file*,int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char const*,...) ; 

__attribute__((used)) static int fm10k_dbg_tx_desc_seq_show(struct seq_file *s, void *v)
{
	struct fm10k_ring *ring = s->private;
	int i = *(loff_t *)v;
	static const char tx_desc_hdr[] =
		"DES BUFFER_ADDRESS     LENGTH VLAN   MSS    HDRLEN FLAGS\n";

	/* Generate header */
	if (!i) {
		seq_printf(s, tx_desc_hdr);
		fm10k_dbg_desc_break(s, sizeof(tx_desc_hdr) - 1);
	}

	/* Validate descriptor allocation */
	if (!ring->desc) {
		seq_printf(s, "%03X Descriptor ring not allocated.\n", i);
	} else {
		struct fm10k_tx_desc *txd = FM10K_TX_DESC(ring, i);

		seq_printf(s, "%03X %#018llx %#06x %#06x %#06x %#06x %#04x\n",
			   i, txd->buffer_addr, txd->buflen, txd->vlan,
			   txd->mss, txd->hdrlen, txd->flags);
	}

	return 0;
}