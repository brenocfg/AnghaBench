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
struct sm501_devdata {scalar_t__ regs; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct sm501_devdata* dev_get_drvdata (struct device*) ; 
 int smc501_readl (scalar_t__) ; 
 int sprintf (char*,char*,unsigned int,int) ; 

__attribute__((used)) static ssize_t sm501_dbg_regs(struct device *dev,
			      struct device_attribute *attr, char *buff)
{
	struct sm501_devdata *sm = dev_get_drvdata(dev)	;
	unsigned int reg;
	char *ptr = buff;
	int ret;

	for (reg = 0x00; reg < 0x70; reg += 4) {
		ret = sprintf(ptr, "%08x = %08x\n",
			      reg, smc501_readl(sm->regs + reg));
		ptr += ret;
	}

	return ptr - buff;
}