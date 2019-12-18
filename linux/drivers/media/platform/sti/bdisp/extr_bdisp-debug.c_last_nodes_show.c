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
struct seq_file {struct bdisp_dev* private; } ;
struct bdisp_node {int nip; int cic; int ack; int tba; int s1ba; int s2ba; int s3ba; int hfp; int vfp; int y_hfp; int y_vfp; int /*<<< orphan*/  ivmx3; int /*<<< orphan*/  ivmx2; int /*<<< orphan*/  ivmx1; int /*<<< orphan*/  ivmx0; int /*<<< orphan*/  y_rzi; int /*<<< orphan*/  y_rsf; int /*<<< orphan*/  rzi; int /*<<< orphan*/  rsf; int /*<<< orphan*/  fctl; int /*<<< orphan*/  s3sz; int /*<<< orphan*/  s3xy; int /*<<< orphan*/  s3ty; int /*<<< orphan*/  s2sz; int /*<<< orphan*/  s2xy; int /*<<< orphan*/  s2ty; int /*<<< orphan*/  s1xy; int /*<<< orphan*/  s1ty; int /*<<< orphan*/  tsz; int /*<<< orphan*/  txy; int /*<<< orphan*/  tty; int /*<<< orphan*/  ins; } ;
struct TYPE_2__ {struct bdisp_node** copy_node; } ;
struct bdisp_dev {TYPE_1__ dbg; } ;

/* Variables and functions */
 int MAX_NB_NODE ; 
 int /*<<< orphan*/  bdisp_dbg_dump_fctl (struct seq_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdisp_dbg_dump_ins (struct seq_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdisp_dbg_dump_ivmx (struct seq_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdisp_dbg_dump_rsf (struct seq_file*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bdisp_dbg_dump_rzi (struct seq_file*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bdisp_dbg_dump_sty (struct seq_file*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  bdisp_dbg_dump_sz (struct seq_file*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bdisp_dbg_dump_tty (struct seq_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdisp_dbg_dump_xy (struct seq_file*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int last_nodes_show(struct seq_file *s, void *data)
{
	/* Not dumping all fields, focusing on significant ones */
	struct bdisp_dev *bdisp = s->private;
	struct bdisp_node *node;
	int i = 0;

	if (!bdisp->dbg.copy_node[0]) {
		seq_puts(s, "No node built yet\n");
		return 0;
	}

	do {
		node = bdisp->dbg.copy_node[i];
		if (!node)
			break;
		seq_printf(s, "--------\nNode %d:\n", i);
		seq_puts(s, "-- General --\n");
		seq_printf(s, "NIP\t0x%08X\n", node->nip);
		seq_printf(s, "CIC\t0x%08X\n", node->cic);
		bdisp_dbg_dump_ins(s, node->ins);
		seq_printf(s, "ACK\t0x%08X\n", node->ack);
		seq_puts(s, "-- Target --\n");
		seq_printf(s, "TBA\t0x%08X\n", node->tba);
		bdisp_dbg_dump_tty(s, node->tty);
		bdisp_dbg_dump_xy(s, node->txy, "TXY");
		bdisp_dbg_dump_sz(s, node->tsz, "TSZ");
		/* Color Fill not dumped */
		seq_puts(s, "-- Source 1 --\n");
		seq_printf(s, "S1BA\t0x%08X\n", node->s1ba);
		bdisp_dbg_dump_sty(s, node->s1ty, node->s1ba, "S1TY");
		bdisp_dbg_dump_xy(s, node->s1xy, "S1XY");
		seq_puts(s, "-- Source 2 --\n");
		seq_printf(s, "S2BA\t0x%08X\n", node->s2ba);
		bdisp_dbg_dump_sty(s, node->s2ty, node->s2ba, "S2TY");
		bdisp_dbg_dump_xy(s, node->s2xy, "S2XY");
		bdisp_dbg_dump_sz(s, node->s2sz, "S2SZ");
		seq_puts(s, "-- Source 3 --\n");
		seq_printf(s, "S3BA\t0x%08X\n", node->s3ba);
		bdisp_dbg_dump_sty(s, node->s3ty, node->s3ba, "S3TY");
		bdisp_dbg_dump_xy(s, node->s3xy, "S3XY");
		bdisp_dbg_dump_sz(s, node->s3sz, "S3SZ");
		/* Clipping not dumped */
		/* CLUT not dumped */
		seq_puts(s, "-- Filter & Mask --\n");
		bdisp_dbg_dump_fctl(s, node->fctl);
		/* PMK not dumped */
		seq_puts(s, "-- Chroma Filter --\n");
		bdisp_dbg_dump_rsf(s, node->rsf, "RSF");
		bdisp_dbg_dump_rzi(s, node->rzi, "RZI");
		seq_printf(s, "HFP\t0x%08X\n", node->hfp);
		seq_printf(s, "VFP\t0x%08X\n", node->vfp);
		seq_puts(s, "-- Luma Filter --\n");
		bdisp_dbg_dump_rsf(s, node->y_rsf, "Y_RSF");
		bdisp_dbg_dump_rzi(s, node->y_rzi, "Y_RZI");
		seq_printf(s, "Y_HFP\t0x%08X\n", node->y_hfp);
		seq_printf(s, "Y_VFP\t0x%08X\n", node->y_vfp);
		/* Flicker not dumped */
		/* Color key not dumped */
		/* Reserved not dumped */
		/* Static Address & User not dumped */
		seq_puts(s, "-- Input Versatile Matrix --\n");
		bdisp_dbg_dump_ivmx(s, node->ivmx0, node->ivmx1,
				    node->ivmx2, node->ivmx3);
		/* Output Versatile Matrix not dumped */
		/* Pace not dumped */
		/* VC1R & DEI not dumped */
		/* Gradient Fill not dumped */
	} while ((++i < MAX_NB_NODE) && node->nip);

	return 0;
}