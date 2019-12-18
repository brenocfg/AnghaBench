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
typedef  scalar_t__ uint64_t ;
typedef  size_t uint ;
typedef  int u32 ;
struct wil_ring_tx_data {int idle; scalar_t__ begin; scalar_t__ dot1x_open; scalar_t__ agg_amsdu; int /*<<< orphan*/  agg_timeout; int /*<<< orphan*/  agg_wsize; } ;
struct wil_ring {int swhead; int swtail; int size; scalar_t__ va; } ;
struct wil6210_priv {int** ring2cid_tid; int max_assoc_sta; TYPE_1__* sta; struct wil_ring_tx_data* ring_tx_data; struct wil_ring* ring_tx; struct wil_ring ring_rx; } ;
struct seq_file {struct wil6210_priv* private; } ;
typedef  int /*<<< orphan*/  sidle ;
typedef  int /*<<< orphan*/  name ;
typedef  scalar_t__ cycles_t ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct wil_ring*) ; 
 int /*<<< orphan*/  do_div (scalar_t__,scalar_t__) ; 
 scalar_t__ get_cycles () ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,int,int,char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  wil_print_ring (struct seq_file*,struct wil6210_priv*,char*,struct wil_ring*,char,char) ; 

__attribute__((used)) static int ring_show(struct seq_file *s, void *data)
{
	uint i;
	struct wil6210_priv *wil = s->private;

	wil_print_ring(s, wil, "rx", &wil->ring_rx, 'S', '_');

	for (i = 0; i < ARRAY_SIZE(wil->ring_tx); i++) {
		struct wil_ring *ring = &wil->ring_tx[i];
		struct wil_ring_tx_data *txdata = &wil->ring_tx_data[i];

		if (ring->va) {
			int cid = wil->ring2cid_tid[i][0];
			int tid = wil->ring2cid_tid[i][1];
			u32 swhead = ring->swhead;
			u32 swtail = ring->swtail;
			int used = (ring->size + swhead - swtail)
				   % ring->size;
			int avail = ring->size - used - 1;
			char name[10];
			char sidle[10];
			/* performance monitoring */
			cycles_t now = get_cycles();
			uint64_t idle = txdata->idle * 100;
			uint64_t total = now - txdata->begin;

			if (total != 0) {
				do_div(idle, total);
				snprintf(sidle, sizeof(sidle), "%3d%%",
					 (int)idle);
			} else {
				snprintf(sidle, sizeof(sidle), "N/A");
			}
			txdata->begin = now;
			txdata->idle = 0ULL;

			snprintf(name, sizeof(name), "tx_%2d", i);

			if (cid < wil->max_assoc_sta)
				seq_printf(s,
					   "\n%pM CID %d TID %d 1x%s BACK([%u] %u TU A%s) [%3d|%3d] idle %s\n",
					   wil->sta[cid].addr, cid, tid,
					   txdata->dot1x_open ? "+" : "-",
					   txdata->agg_wsize,
					   txdata->agg_timeout,
					   txdata->agg_amsdu ? "+" : "-",
					   used, avail, sidle);
			else
				seq_printf(s,
					   "\nBroadcast 1x%s [%3d|%3d] idle %s\n",
					   txdata->dot1x_open ? "+" : "-",
					   used, avail, sidle);

			wil_print_ring(s, wil, name, ring, '_', 'H');
		}
	}

	return 0;
}