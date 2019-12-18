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
struct sram_channel {int /*<<< orphan*/  dma_ctl; } ;
struct file {int dummy; } ;
struct cx25821_dev {int dummy; } ;
struct cx25821_channel {struct sram_channel* sram_channels; struct cx25821_dev* dev; } ;

/* Variables and functions */
 int cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 struct cx25821_channel* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_log_status(struct file *file, void *priv)
{
	struct cx25821_channel *chan = video_drvdata(file);
	struct cx25821_dev *dev = chan->dev;
	const struct sram_channel *sram_ch = chan->sram_channels;
	u32 tmp = 0;

	tmp = cx_read(sram_ch->dma_ctl);
	pr_info("Video input 0 is %s\n",
		(tmp & 0x11) ? "streaming" : "stopped");
	return 0;
}