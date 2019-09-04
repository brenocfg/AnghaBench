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
struct saa7134_dev {int /*<<< orphan*/  slock; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7134_IRQ1 ; 
 int /*<<< orphan*/  SAA7134_IRQ2 ; 
 int /*<<< orphan*/  SAA7134_IRQ_REPORT ; 
 scalar_t__ card_has_mpeg (struct saa7134_dev*) ; 
 int /*<<< orphan*/  core_dbg (char*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  saa7134_hw_enable1 (struct saa7134_dev*) ; 
 int /*<<< orphan*/  saa7134_input_init1 (struct saa7134_dev*) ; 
 int /*<<< orphan*/  saa7134_track_gpio (struct saa7134_dev*,char*) ; 
 int /*<<< orphan*/  saa7134_ts_init1 (struct saa7134_dev*) ; 
 int /*<<< orphan*/  saa7134_vbi_init1 (struct saa7134_dev*) ; 
 int /*<<< orphan*/  saa7134_video_init1 (struct saa7134_dev*) ; 
 int /*<<< orphan*/  saa_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int saa7134_hwinit1(struct saa7134_dev *dev)
{
	core_dbg("hwinit1\n");

	saa_writel(SAA7134_IRQ1, 0);
	saa_writel(SAA7134_IRQ2, 0);

	/* Clear any stale IRQ reports */
	saa_writel(SAA7134_IRQ_REPORT, saa_readl(SAA7134_IRQ_REPORT));

	mutex_init(&dev->lock);
	spin_lock_init(&dev->slock);

	saa7134_track_gpio(dev,"pre-init");
	saa7134_video_init1(dev);
	saa7134_vbi_init1(dev);
	if (card_has_mpeg(dev))
		saa7134_ts_init1(dev);
	saa7134_input_init1(dev);

	saa7134_hw_enable1(dev);

	return 0;
}