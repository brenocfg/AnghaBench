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
struct osd_state {int dummy; } ;
typedef  enum osd_pix_format { ____Placeholder_osd_pix_format } osd_pix_format ;

/* Variables and functions */
 int /*<<< orphan*/  OSD_MODE ; 
 int /*<<< orphan*/  OSD_MODE_CS ; 
 int PIXFMT_YCBCRI ; 
 int PIXFMT_YCRCBI ; 
 int /*<<< orphan*/  osd_clear (struct osd_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osd_set (struct osd_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _osd_set_cbcr_order(struct osd_state *sd,
				enum osd_pix_format pixfmt)
{
	/*
	 * The caller must ensure that all windows using YC pixfmt use the same
	 * Cb/Cr order.
	 */
	if (pixfmt == PIXFMT_YCBCRI)
		osd_clear(sd, OSD_MODE_CS, OSD_MODE);
	else if (pixfmt == PIXFMT_YCRCBI)
		osd_set(sd, OSD_MODE_CS, OSD_MODE);
}