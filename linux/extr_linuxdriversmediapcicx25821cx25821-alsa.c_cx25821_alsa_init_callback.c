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
struct v4l2_device {int dummy; } ;
struct device {int dummy; } ;
struct cx25821_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx25821_audio_initdev (struct cx25821_dev*) ; 
 struct v4l2_device* dev_get_drvdata (struct device*) ; 
 struct cx25821_dev* get_cx25821 (struct v4l2_device*) ; 

__attribute__((used)) static int cx25821_alsa_init_callback(struct device *dev, void *data)
{
	struct v4l2_device *v4l2_dev = dev_get_drvdata(dev);
	struct cx25821_dev *cxdev = get_cx25821(v4l2_dev);

	cx25821_audio_initdev(cxdev);
	return 0;
}