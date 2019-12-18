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
struct vpdma_dtd {int /*<<< orphan*/ * client_attr1; int /*<<< orphan*/ * client_attr0; int /*<<< orphan*/  start_addr; } ;

/* Variables and functions */
 int DTD_DIR_IN ; 
 int DTD_DIR_OUT ; 
 int /*<<< orphan*/  dtd_get_1d (struct vpdma_dtd*) ; 
 int dtd_get_chan (struct vpdma_dtd*) ; 
 int /*<<< orphan*/  dtd_get_data_type (struct vpdma_dtd*) ; 
 int /*<<< orphan*/  dtd_get_desc_write_addr (struct vpdma_dtd*) ; 
 int dtd_get_dir (struct vpdma_dtd*) ; 
 int /*<<< orphan*/  dtd_get_drop_data (struct vpdma_dtd*) ; 
 int /*<<< orphan*/  dtd_get_even_line_skip (struct vpdma_dtd*) ; 
 int /*<<< orphan*/  dtd_get_field (struct vpdma_dtd*) ; 
 int /*<<< orphan*/  dtd_get_frame_height (struct vpdma_dtd*) ; 
 int /*<<< orphan*/  dtd_get_frame_width (struct vpdma_dtd*) ; 
 int /*<<< orphan*/  dtd_get_h_start (struct vpdma_dtd*) ; 
 int /*<<< orphan*/  dtd_get_line_length (struct vpdma_dtd*) ; 
 int /*<<< orphan*/  dtd_get_line_stride (struct vpdma_dtd*) ; 
 int /*<<< orphan*/  dtd_get_max_height (struct vpdma_dtd*) ; 
 int /*<<< orphan*/  dtd_get_max_width (struct vpdma_dtd*) ; 
 int /*<<< orphan*/  dtd_get_mode (struct vpdma_dtd*) ; 
 int /*<<< orphan*/  dtd_get_next_chan (struct vpdma_dtd*) ; 
 int /*<<< orphan*/  dtd_get_notify (struct vpdma_dtd*) ; 
 int /*<<< orphan*/  dtd_get_odd_line_skip (struct vpdma_dtd*) ; 
 int /*<<< orphan*/  dtd_get_pkt_type (struct vpdma_dtd*) ; 
 int /*<<< orphan*/  dtd_get_priority (struct vpdma_dtd*) ; 
 int /*<<< orphan*/  dtd_get_use_desc (struct vpdma_dtd*) ; 
 int /*<<< orphan*/  dtd_get_v_start (struct vpdma_dtd*) ; 
 int /*<<< orphan*/  dtd_get_write_desc (struct vpdma_dtd*) ; 
 int /*<<< orphan*/  dtd_get_xfer_height (struct vpdma_dtd*) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,...) ; 

__attribute__((used)) static void dump_dtd(struct vpdma_dtd *dtd)
{
	int dir, chan;

	dir = dtd_get_dir(dtd);
	chan = dtd_get_chan(dtd);

	pr_debug("%s data transfer descriptor for channel %d\n",
		dir == DTD_DIR_OUT ? "outbound" : "inbound", chan);

	pr_debug("word0: data_type = %d, notify = %d, field = %d, 1D = %d, even_ln_skp = %d, odd_ln_skp = %d, line_stride = %d\n",
		dtd_get_data_type(dtd), dtd_get_notify(dtd), dtd_get_field(dtd),
		dtd_get_1d(dtd), dtd_get_even_line_skip(dtd),
		dtd_get_odd_line_skip(dtd), dtd_get_line_stride(dtd));

	if (dir == DTD_DIR_IN)
		pr_debug("word1: line_length = %d, xfer_height = %d\n",
			dtd_get_line_length(dtd), dtd_get_xfer_height(dtd));

	pr_debug("word2: start_addr = %pad\n", &dtd->start_addr);

	pr_debug("word3: pkt_type = %d, mode = %d, dir = %d, chan = %d, pri = %d, next_chan = %d\n",
		 dtd_get_pkt_type(dtd),
		 dtd_get_mode(dtd), dir, chan, dtd_get_priority(dtd),
		 dtd_get_next_chan(dtd));

	if (dir == DTD_DIR_IN)
		pr_debug("word4: frame_width = %d, frame_height = %d\n",
			dtd_get_frame_width(dtd), dtd_get_frame_height(dtd));
	else
		pr_debug("word4: desc_write_addr = 0x%08x, write_desc = %d, drp_data = %d, use_desc_reg = %d\n",
			dtd_get_desc_write_addr(dtd), dtd_get_write_desc(dtd),
			dtd_get_drop_data(dtd), dtd_get_use_desc(dtd));

	if (dir == DTD_DIR_IN)
		pr_debug("word5: hor_start = %d, ver_start = %d\n",
			dtd_get_h_start(dtd), dtd_get_v_start(dtd));
	else
		pr_debug("word5: max_width %d, max_height %d\n",
			dtd_get_max_width(dtd), dtd_get_max_height(dtd));

	pr_debug("word6: client specific attr0 = 0x%08x\n", dtd->client_attr0);
	pr_debug("word7: client specific attr1 = 0x%08x\n", dtd->client_attr1);
}