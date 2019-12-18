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
struct solo_dev {scalar_t__ type; unsigned long video_hsize; unsigned long video_vsize; int nr_chans; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SOLO_CAP_BASE ; 
 int SOLO_CAP_BASE_ADDR (int) ; 
 int /*<<< orphan*/  SOLO_CAP_BTW ; 
 int SOLO_CAP_EXT_ADDR (struct solo_dev*) ; 
 int SOLO_CAP_EXT_SIZE (struct solo_dev*) ; 
 int SOLO_CAP_MAX_BANDWIDTH (int) ; 
 int SOLO_CAP_MAX_PAGE (int) ; 
 int SOLO_CAP_PAGE_SIZE ; 
 int SOLO_CAP_PROG_BANDWIDTH (int) ; 
 scalar_t__ SOLO_DEV_6010 ; 
 scalar_t__ SOLO_DEV_6110 ; 
 int SOLO_DIM_H_MB_NUM (unsigned long) ; 
 int /*<<< orphan*/  SOLO_DIM_PROG ; 
 int /*<<< orphan*/  SOLO_DIM_SCALE1 ; 
 int /*<<< orphan*/  SOLO_DIM_SCALE2 ; 
 int /*<<< orphan*/  SOLO_DIM_SCALE3 ; 
 int /*<<< orphan*/  SOLO_DIM_SCALE4 ; 
 int /*<<< orphan*/  SOLO_DIM_SCALE5 ; 
 int SOLO_DIM_V_MB_NUM_FIELD (unsigned long) ; 
 int SOLO_DIM_V_MB_NUM_FRAME (unsigned long) ; 
 int SOLO_EOSD_EXT_ADDR ; 
 int SOLO_EOSD_EXT_SIZE (struct solo_dev*) ; 
 int /*<<< orphan*/  SOLO_VE_OSD_BASE ; 
 int /*<<< orphan*/  SOLO_VE_OSD_CH ; 
 int /*<<< orphan*/  SOLO_VE_OSD_CLR ; 
 int SOLO_VE_OSD_H_SHADOW ; 
 int /*<<< orphan*/  SOLO_VE_OSD_OPT ; 
 int SOLO_VE_OSD_V_DOUBLE ; 
 int SOLO_VE_OSD_V_SHADOW ; 
 unsigned long VI_PROG_HSIZE ; 
 unsigned long VI_PROG_VSIZE ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  solo_p2m_dma (struct solo_dev*,int,void*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  solo_reg_write (struct solo_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void solo_capture_config(struct solo_dev *solo_dev)
{
	unsigned long height;
	unsigned long width;
	void *buf;
	int i;

	solo_reg_write(solo_dev, SOLO_CAP_BASE,
		       SOLO_CAP_MAX_PAGE((SOLO_CAP_EXT_SIZE(solo_dev)
					  - SOLO_CAP_PAGE_SIZE) >> 16)
		       | SOLO_CAP_BASE_ADDR(SOLO_CAP_EXT_ADDR(solo_dev) >> 16));

	/* XXX: Undocumented bits at b17 and b24 */
	if (solo_dev->type == SOLO_DEV_6110) {
		/* NOTE: Ref driver has (62 << 24) here as well, but it causes
		 * wacked out frame timing on 4-port 6110. */
		solo_reg_write(solo_dev, SOLO_CAP_BTW,
			       (1 << 17) | SOLO_CAP_PROG_BANDWIDTH(2) |
			       SOLO_CAP_MAX_BANDWIDTH(36));
	} else {
		solo_reg_write(solo_dev, SOLO_CAP_BTW,
			       (1 << 17) | SOLO_CAP_PROG_BANDWIDTH(2) |
			       SOLO_CAP_MAX_BANDWIDTH(32));
	}

	/* Set scale 1, 9 dimension */
	width = solo_dev->video_hsize;
	height = solo_dev->video_vsize;
	solo_reg_write(solo_dev, SOLO_DIM_SCALE1,
		       SOLO_DIM_H_MB_NUM(width / 16) |
		       SOLO_DIM_V_MB_NUM_FRAME(height / 8) |
		       SOLO_DIM_V_MB_NUM_FIELD(height / 16));

	/* Set scale 2, 10 dimension */
	width = solo_dev->video_hsize / 2;
	height = solo_dev->video_vsize;
	solo_reg_write(solo_dev, SOLO_DIM_SCALE2,
		       SOLO_DIM_H_MB_NUM(width / 16) |
		       SOLO_DIM_V_MB_NUM_FRAME(height / 8) |
		       SOLO_DIM_V_MB_NUM_FIELD(height / 16));

	/* Set scale 3, 11 dimension */
	width = solo_dev->video_hsize / 2;
	height = solo_dev->video_vsize / 2;
	solo_reg_write(solo_dev, SOLO_DIM_SCALE3,
		       SOLO_DIM_H_MB_NUM(width / 16) |
		       SOLO_DIM_V_MB_NUM_FRAME(height / 8) |
		       SOLO_DIM_V_MB_NUM_FIELD(height / 16));

	/* Set scale 4, 12 dimension */
	width = solo_dev->video_hsize / 3;
	height = solo_dev->video_vsize / 3;
	solo_reg_write(solo_dev, SOLO_DIM_SCALE4,
		       SOLO_DIM_H_MB_NUM(width / 16) |
		       SOLO_DIM_V_MB_NUM_FRAME(height / 8) |
		       SOLO_DIM_V_MB_NUM_FIELD(height / 16));

	/* Set scale 5, 13 dimension */
	width = solo_dev->video_hsize / 4;
	height = solo_dev->video_vsize / 2;
	solo_reg_write(solo_dev, SOLO_DIM_SCALE5,
		       SOLO_DIM_H_MB_NUM(width / 16) |
		       SOLO_DIM_V_MB_NUM_FRAME(height / 8) |
		       SOLO_DIM_V_MB_NUM_FIELD(height / 16));

	/* Progressive */
	width = VI_PROG_HSIZE;
	height = VI_PROG_VSIZE;
	solo_reg_write(solo_dev, SOLO_DIM_PROG,
		       SOLO_DIM_H_MB_NUM(width / 16) |
		       SOLO_DIM_V_MB_NUM_FRAME(height / 16) |
		       SOLO_DIM_V_MB_NUM_FIELD(height / 16));

	/* Clear OSD */
	solo_reg_write(solo_dev, SOLO_VE_OSD_CH, 0);
	solo_reg_write(solo_dev, SOLO_VE_OSD_BASE, SOLO_EOSD_EXT_ADDR >> 16);
	solo_reg_write(solo_dev, SOLO_VE_OSD_CLR,
		       0xF0 << 16 | 0x80 << 8 | 0x80);

	if (solo_dev->type == SOLO_DEV_6010)
		solo_reg_write(solo_dev, SOLO_VE_OSD_OPT,
			       SOLO_VE_OSD_H_SHADOW | SOLO_VE_OSD_V_SHADOW);
	else
		solo_reg_write(solo_dev, SOLO_VE_OSD_OPT, SOLO_VE_OSD_V_DOUBLE
			       | SOLO_VE_OSD_H_SHADOW | SOLO_VE_OSD_V_SHADOW);

	/* Clear OSG buffer */
	buf = kzalloc(SOLO_EOSD_EXT_SIZE(solo_dev), GFP_KERNEL);
	if (!buf)
		return;

	for (i = 0; i < solo_dev->nr_chans; i++) {
		solo_p2m_dma(solo_dev, 1, buf,
			     SOLO_EOSD_EXT_ADDR +
			     (SOLO_EOSD_EXT_SIZE(solo_dev) * i),
			     SOLO_EOSD_EXT_SIZE(solo_dev), 0, 0);
	}
	kfree(buf);
}