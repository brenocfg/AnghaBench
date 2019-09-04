#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  timestamp; } ;
struct TYPE_5__ {int /*<<< orphan*/  sglort; int /*<<< orphan*/  dglort; int /*<<< orphan*/  vlan; int /*<<< orphan*/  length; } ;
struct TYPE_4__ {int /*<<< orphan*/  staterr; int /*<<< orphan*/  rss; int /*<<< orphan*/  data; } ;
union fm10k_rx_desc {TYPE_3__ q; TYPE_2__ w; TYPE_1__ d; } ;
struct seq_file {struct fm10k_ring* private; } ;
struct fm10k_ring {int /*<<< orphan*/  desc; } ;
typedef  int /*<<< orphan*/  rx_desc_hdr ;
typedef  int loff_t ;

/* Variables and functions */
 union fm10k_rx_desc* FM10K_RX_DESC (struct fm10k_ring*,int) ; 
 int /*<<< orphan*/  fm10k_dbg_desc_break (struct seq_file*,int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char const*,...) ; 

__attribute__((used)) static int fm10k_dbg_rx_desc_seq_show(struct seq_file *s, void *v)
{
	struct fm10k_ring *ring = s->private;
	int i = *(loff_t *)v;
	static const char rx_desc_hdr[] =
	"DES DATA       RSS        STATERR    LENGTH VLAN   DGLORT SGLORT TIMESTAMP\n";

	/* Generate header */
	if (!i) {
		seq_printf(s, rx_desc_hdr);
		fm10k_dbg_desc_break(s, sizeof(rx_desc_hdr) - 1);
	}

	/* Validate descriptor allocation */
	if (!ring->desc) {
		seq_printf(s, "%03X Descriptor ring not allocated.\n", i);
	} else {
		union fm10k_rx_desc *rxd = FM10K_RX_DESC(ring, i);

		seq_printf(s,
			   "%03X %#010x %#010x %#010x %#06x %#06x %#06x %#06x %#018llx\n",
			   i, rxd->d.data, rxd->d.rss, rxd->d.staterr,
			   rxd->w.length, rxd->w.vlan, rxd->w.dglort,
			   rxd->w.sglort, rxd->q.timestamp);
	}

	return 0;
}