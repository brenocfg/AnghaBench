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
struct ufs_clk_scaling {int is_busy_started; scalar_t__ busy_start_t; scalar_t__ tot_busy_t; scalar_t__ window_start_t; } ;
struct ufs_hba {TYPE_1__* host; scalar_t__ outstanding_reqs; struct ufs_clk_scaling clk_scaling; } ;
struct device {int dummy; } ;
struct devfreq_dev_status {scalar_t__ busy_time; int /*<<< orphan*/  total_time; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 struct ufs_hba* dev_get_drvdata (struct device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  jiffies_to_usecs (long) ; 
 scalar_t__ ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (scalar_t__,scalar_t__) ; 
 scalar_t__ ktime_to_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct devfreq_dev_status*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ufshcd_is_clkscaling_supported (struct ufs_hba*) ; 

__attribute__((used)) static int ufshcd_devfreq_get_dev_status(struct device *dev,
		struct devfreq_dev_status *stat)
{
	struct ufs_hba *hba = dev_get_drvdata(dev);
	struct ufs_clk_scaling *scaling = &hba->clk_scaling;
	unsigned long flags;

	if (!ufshcd_is_clkscaling_supported(hba))
		return -EINVAL;

	memset(stat, 0, sizeof(*stat));

	spin_lock_irqsave(hba->host->host_lock, flags);
	if (!scaling->window_start_t)
		goto start_window;

	if (scaling->is_busy_started)
		scaling->tot_busy_t += ktime_to_us(ktime_sub(ktime_get(),
					scaling->busy_start_t));

	stat->total_time = jiffies_to_usecs((long)jiffies -
				(long)scaling->window_start_t);
	stat->busy_time = scaling->tot_busy_t;
start_window:
	scaling->window_start_t = jiffies;
	scaling->tot_busy_t = 0;

	if (hba->outstanding_reqs) {
		scaling->busy_start_t = ktime_get();
		scaling->is_busy_started = true;
	} else {
		scaling->busy_start_t = 0;
		scaling->is_busy_started = false;
	}
	spin_unlock_irqrestore(hba->host->host_lock, flags);
	return 0;
}