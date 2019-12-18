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
struct sh_rtc {scalar_t__ regbase; } ;
struct seq_file {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ RCR1 ; 
 unsigned int RCR1_CIE ; 
 scalar_t__ RCR2 ; 
 unsigned int RCR2_PESMASK ; 
 struct sh_rtc* dev_get_drvdata (struct device*) ; 
 unsigned int readb (scalar_t__) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*) ; 

__attribute__((used)) static int sh_rtc_proc(struct device *dev, struct seq_file *seq)
{
	struct sh_rtc *rtc = dev_get_drvdata(dev);
	unsigned int tmp;

	tmp = readb(rtc->regbase + RCR1);
	seq_printf(seq, "carry_IRQ\t: %s\n", (tmp & RCR1_CIE) ? "yes" : "no");

	tmp = readb(rtc->regbase + RCR2);
	seq_printf(seq, "periodic_IRQ\t: %s\n",
		   (tmp & RCR2_PESMASK) ? "yes" : "no");

	return 0;
}