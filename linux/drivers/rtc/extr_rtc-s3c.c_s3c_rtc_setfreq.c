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
struct s3c_rtc {int /*<<< orphan*/  pie_lock; TYPE_1__* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_freq ) (struct s3c_rtc*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 int /*<<< orphan*/  s3c_rtc_disable_clk (struct s3c_rtc*) ; 
 int s3c_rtc_enable_clk (struct s3c_rtc*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct s3c_rtc*,int) ; 

__attribute__((used)) static int s3c_rtc_setfreq(struct s3c_rtc *info, int freq)
{
	int ret;

	if (!is_power_of_2(freq))
		return -EINVAL;

	ret = s3c_rtc_enable_clk(info);
	if (ret)
		return ret;
	spin_lock_irq(&info->pie_lock);

	if (info->data->set_freq)
		info->data->set_freq(info, freq);

	spin_unlock_irq(&info->pie_lock);
	s3c_rtc_disable_clk(info);

	return 0;
}