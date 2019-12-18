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
struct seq_file {int dummy; } ;
struct s3c_rtc {TYPE_1__* data; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable_tick ) (struct s3c_rtc*,struct seq_file*) ;} ;

/* Variables and functions */
 struct s3c_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  s3c_rtc_disable_clk (struct s3c_rtc*) ; 
 int s3c_rtc_enable_clk (struct s3c_rtc*) ; 
 int /*<<< orphan*/  stub1 (struct s3c_rtc*,struct seq_file*) ; 

__attribute__((used)) static int s3c_rtc_proc(struct device *dev, struct seq_file *seq)
{
	struct s3c_rtc *info = dev_get_drvdata(dev);
	int ret;

	ret = s3c_rtc_enable_clk(info);
	if (ret)
		return ret;

	if (info->data->enable_tick)
		info->data->enable_tick(info, seq);

	s3c_rtc_disable_clk(info);

	return 0;
}