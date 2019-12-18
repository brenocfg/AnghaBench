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
typedef  int u32 ;
struct wil_status_ring {int* va; int size; int elem_size; int /*<<< orphan*/  is_rx; } ;
struct wil6210_priv {int /*<<< orphan*/  use_compressed_rx_status; struct wil_status_ring* srings; } ;
struct seq_file {struct wil6210_priv* private; } ;

/* Variables and functions */
 int WIL6210_MAX_STATUS_RINGS ; 
 int dbg_sring_index ; 
 int dbg_status_msg_index ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int status_msg_show(struct seq_file *s, void *data)
{
	struct wil6210_priv *wil = s->private;
	int sring_idx = dbg_sring_index;
	struct wil_status_ring *sring;
	bool tx;
	u32 status_msg_idx = dbg_status_msg_index;
	u32 *u;

	if (sring_idx >= WIL6210_MAX_STATUS_RINGS) {
		seq_printf(s, "invalid status ring index %d\n", sring_idx);
		return 0;
	}

	sring = &wil->srings[sring_idx];
	tx = !sring->is_rx;

	if (!sring->va) {
		seq_printf(s, "No %cX status ring\n", tx ? 'T' : 'R');
		return 0;
	}

	if (status_msg_idx >= sring->size) {
		seq_printf(s, "%cxDesc index (%d) >= size (%d)\n",
			   tx ? 'T' : 'R', status_msg_idx, sring->size);
		return 0;
	}

	u = sring->va + (sring->elem_size * status_msg_idx);

	seq_printf(s, "%cx[%d][%3d] = {\n",
		   tx ? 'T' : 'R', sring_idx, status_msg_idx);

	seq_printf(s, "  0x%08x 0x%08x 0x%08x 0x%08x\n",
		   u[0], u[1], u[2], u[3]);
	if (!tx && !wil->use_compressed_rx_status)
		seq_printf(s, "  0x%08x 0x%08x 0x%08x 0x%08x\n",
			   u[4], u[5], u[6], u[7]);

	seq_puts(s, "}\n");

	return 0;
}