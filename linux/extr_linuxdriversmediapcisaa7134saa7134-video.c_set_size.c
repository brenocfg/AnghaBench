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
struct TYPE_2__ {int left; int top; int width; int height; } ;
struct saa7134_dev {int ctl_y_odd; int ctl_y_even; TYPE_1__ crop_current; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7134_H_SCALE_INC1 (int) ; 
 int /*<<< orphan*/  SAA7134_H_SCALE_INC2 (int) ; 
 int /*<<< orphan*/  SAA7134_VIDEO_H_START1 (int) ; 
 int /*<<< orphan*/  SAA7134_VIDEO_H_START2 (int) ; 
 int /*<<< orphan*/  SAA7134_VIDEO_H_STOP1 (int) ; 
 int /*<<< orphan*/  SAA7134_VIDEO_H_STOP2 (int) ; 
 int /*<<< orphan*/  SAA7134_VIDEO_LINES1 (int) ; 
 int /*<<< orphan*/  SAA7134_VIDEO_LINES2 (int) ; 
 int /*<<< orphan*/  SAA7134_VIDEO_PIXELS1 (int) ; 
 int /*<<< orphan*/  SAA7134_VIDEO_PIXELS2 (int) ; 
 int /*<<< orphan*/  SAA7134_VIDEO_V_START1 (int) ; 
 int /*<<< orphan*/  SAA7134_VIDEO_V_START2 (int) ; 
 int /*<<< orphan*/  SAA7134_VIDEO_V_STOP1 (int) ; 
 int /*<<< orphan*/  SAA7134_VIDEO_V_STOP2 (int) ; 
 int /*<<< orphan*/  SAA7134_V_PHASE_OFFSET0 (int) ; 
 int /*<<< orphan*/  SAA7134_V_PHASE_OFFSET1 (int) ; 
 int /*<<< orphan*/  SAA7134_V_PHASE_OFFSET2 (int) ; 
 int /*<<< orphan*/  SAA7134_V_PHASE_OFFSET3 (int) ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_h_prescale (struct saa7134_dev*,int,int) ; 
 int /*<<< orphan*/  set_v_scale (struct saa7134_dev*,int,int) ; 
 int /*<<< orphan*/  video_dbg (char*,int,int,int) ; 

__attribute__((used)) static void set_size(struct saa7134_dev *dev, int task,
		     int width, int height, int interlace)
{
	int prescale,xscale,yscale,y_even,y_odd;
	int h_start, h_stop, v_start, v_stop;
	int div = interlace ? 2 : 1;

	/* setup video scaler */
	h_start = dev->crop_current.left;
	v_start = dev->crop_current.top/2;
	h_stop  = (dev->crop_current.left + dev->crop_current.width -1);
	v_stop  = (dev->crop_current.top + dev->crop_current.height -1)/2;

	saa_writeb(SAA7134_VIDEO_H_START1(task), h_start &  0xff);
	saa_writeb(SAA7134_VIDEO_H_START2(task), h_start >> 8);
	saa_writeb(SAA7134_VIDEO_H_STOP1(task),  h_stop  &  0xff);
	saa_writeb(SAA7134_VIDEO_H_STOP2(task),  h_stop  >> 8);
	saa_writeb(SAA7134_VIDEO_V_START1(task), v_start &  0xff);
	saa_writeb(SAA7134_VIDEO_V_START2(task), v_start >> 8);
	saa_writeb(SAA7134_VIDEO_V_STOP1(task),  v_stop  &  0xff);
	saa_writeb(SAA7134_VIDEO_V_STOP2(task),  v_stop  >> 8);

	prescale = dev->crop_current.width / width;
	if (0 == prescale)
		prescale = 1;
	xscale = 1024 * dev->crop_current.width / prescale / width;
	yscale = 512 * div * dev->crop_current.height / height;
	video_dbg("prescale=%d xscale=%d yscale=%d\n",
		  prescale, xscale, yscale);
	set_h_prescale(dev,task,prescale);
	saa_writeb(SAA7134_H_SCALE_INC1(task),      xscale &  0xff);
	saa_writeb(SAA7134_H_SCALE_INC2(task),      xscale >> 8);
	set_v_scale(dev,task,yscale);

	saa_writeb(SAA7134_VIDEO_PIXELS1(task),     width  & 0xff);
	saa_writeb(SAA7134_VIDEO_PIXELS2(task),     width  >> 8);
	saa_writeb(SAA7134_VIDEO_LINES1(task),      height/div & 0xff);
	saa_writeb(SAA7134_VIDEO_LINES2(task),      height/div >> 8);

	/* deinterlace y offsets */
	y_odd  = dev->ctl_y_odd;
	y_even = dev->ctl_y_even;
	saa_writeb(SAA7134_V_PHASE_OFFSET0(task), y_odd);
	saa_writeb(SAA7134_V_PHASE_OFFSET1(task), y_even);
	saa_writeb(SAA7134_V_PHASE_OFFSET2(task), y_odd);
	saa_writeb(SAA7134_V_PHASE_OFFSET3(task), y_even);
}