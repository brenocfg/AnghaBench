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
struct v4l2_frequency {int dummy; } ;
struct file {int dummy; } ;
struct cx23885_dev {int board; } ;

/* Variables and functions */
#define  CX23885_BOARD_HAUPPAUGE_HVR1255 131 
#define  CX23885_BOARD_HAUPPAUGE_HVR1255_22111 130 
#define  CX23885_BOARD_HAUPPAUGE_HVR1265_K4 129 
#define  CX23885_BOARD_HAUPPAUGE_HVR1850 128 
 int cx23885_set_freq (struct cx23885_dev*,struct v4l2_frequency const*) ; 
 int cx23885_set_freq_via_ops (struct cx23885_dev*,struct v4l2_frequency const*) ; 
 struct cx23885_dev* video_drvdata (struct file*) ; 

int cx23885_set_frequency(struct file *file, void *priv,
	const struct v4l2_frequency *f)
{
	struct cx23885_dev *dev = video_drvdata(file);
	int ret;

	switch (dev->board) {
	case CX23885_BOARD_HAUPPAUGE_HVR1255:
	case CX23885_BOARD_HAUPPAUGE_HVR1255_22111:
	case CX23885_BOARD_HAUPPAUGE_HVR1265_K4:
	case CX23885_BOARD_HAUPPAUGE_HVR1850:
		ret = cx23885_set_freq_via_ops(dev, f);
		break;
	default:
		ret = cx23885_set_freq(dev, f);
	}

	return ret;
}