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
 int /*<<< orphan*/  M48T86_B ; 
 unsigned char M48T86_B_DM ; 
 int /*<<< orphan*/  M48T86_D ; 
 unsigned char M48T86_D_VRT ; 
 unsigned char m48t86_readb (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*) ; 

__attribute__((used)) static int m48t86_rtc_proc(struct device *dev, struct seq_file *seq)
{
	unsigned char reg;

	reg = m48t86_readb(dev, M48T86_B);

	seq_printf(seq, "mode\t\t: %s\n",
		   (reg & M48T86_B_DM) ? "binary" : "bcd");

	reg = m48t86_readb(dev, M48T86_D);

	seq_printf(seq, "battery\t\t: %s\n",
		   (reg & M48T86_D_VRT) ? "ok" : "exhausted");

	return 0;
}