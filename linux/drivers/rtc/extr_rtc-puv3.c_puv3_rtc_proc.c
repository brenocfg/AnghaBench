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
struct seq_file {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_RTSR ; 
 int RTC_RTSR_HZE ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*) ; 

__attribute__((used)) static int puv3_rtc_proc(struct device *dev, struct seq_file *seq)
{
	seq_printf(seq, "periodic_IRQ\t: %s\n",
		     (readl(RTC_RTSR) & RTC_RTSR_HZE) ? "yes" : "no");
	return 0;
}