#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__ v4l2_dev; } ;
struct sh_mobile_ceu_dev {TYPE_2__ ici; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAPSR ; 
 int /*<<< orphan*/  CSTSR ; 
 int HZ ; 
 int ceu_read (struct sh_mobile_ceu_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceu_write (struct sh_mobile_ceu_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_after (int,unsigned long) ; 
 scalar_t__ time_before (int,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void capture_restore(struct sh_mobile_ceu_dev *pcdev, u32 capsr)
{
	unsigned long timeout = jiffies + 10 * HZ;

	/*
	 * Wait until the end of the current frame. It can take a long time,
	 * but if it has been aborted by a CAPSR reset, it shoule exit sooner.
	 */
	while ((ceu_read(pcdev, CSTSR) & 1) && time_before(jiffies, timeout))
		msleep(1);

	if (time_after(jiffies, timeout)) {
		dev_err(pcdev->ici.v4l2_dev.dev,
			"Timeout waiting for frame end! Interface problem?\n");
		return;
	}

	/* Wait until reset clears, this shall not hang... */
	while (ceu_read(pcdev, CAPSR) & (1 << 16))
		udelay(10);

	/* Anything to restore? */
	if (capsr & ~(1 << 16))
		ceu_write(pcdev, CAPSR, capsr);
}