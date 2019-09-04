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
struct saa7134_dev {scalar_t__ ctl_mirror; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7134_CHROMA_SATURATION (int) ; 
 int /*<<< orphan*/  SAA7134_LUMA_BRIGHT (int) ; 
 int /*<<< orphan*/  SAA7134_LUMA_CONTRAST (int) ; 
 int /*<<< orphan*/  SAA7134_V_FILTER (int) ; 
 int /*<<< orphan*/  SAA7134_V_SCALE_RATIO1 (int) ; 
 int /*<<< orphan*/  SAA7134_V_SCALE_RATIO2 (int) ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_dbg (char*,int,...) ; 

__attribute__((used)) static void set_v_scale(struct saa7134_dev *dev, int task, int yscale)
{
	int val,mirror;

	saa_writeb(SAA7134_V_SCALE_RATIO1(task), yscale &  0xff);
	saa_writeb(SAA7134_V_SCALE_RATIO2(task), yscale >> 8);

	mirror = (dev->ctl_mirror) ? 0x02 : 0x00;
	if (yscale < 2048) {
		/* LPI */
		video_dbg("yscale LPI yscale=%d\n", yscale);
		saa_writeb(SAA7134_V_FILTER(task), 0x00 | mirror);
		saa_writeb(SAA7134_LUMA_CONTRAST(task), 0x40);
		saa_writeb(SAA7134_CHROMA_SATURATION(task), 0x40);
	} else {
		/* ACM */
		val = 0x40 * 1024 / yscale;
		video_dbg("yscale ACM yscale=%d val=0x%x\n", yscale, val);
		saa_writeb(SAA7134_V_FILTER(task), 0x01 | mirror);
		saa_writeb(SAA7134_LUMA_CONTRAST(task), val);
		saa_writeb(SAA7134_CHROMA_SATURATION(task), val);
	}
	saa_writeb(SAA7134_LUMA_BRIGHT(task),       0x80);
}