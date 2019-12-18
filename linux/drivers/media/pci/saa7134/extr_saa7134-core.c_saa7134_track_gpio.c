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
struct saa7134_dev {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int SAA7134_GPIO_GPMODE0 ; 
 int /*<<< orphan*/  SAA7134_GPIO_GPMODE3 ; 
 int /*<<< orphan*/  SAA7134_GPIO_GPRESCAN ; 
 int SAA7134_GPIO_GPSTATUS0 ; 
 int /*<<< orphan*/  core_dbg (char*,int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long,char const*) ; 
 int /*<<< orphan*/  gpio_tracking ; 
 int /*<<< orphan*/  saa_andorb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int saa_readl (int) ; 

void saa7134_track_gpio(struct saa7134_dev *dev, const char *msg)
{
	unsigned long mode,status;

	if (!gpio_tracking)
		return;
	/* rising SAA7134_GPIO_GPRESCAN reads the status */
	saa_andorb(SAA7134_GPIO_GPMODE3,SAA7134_GPIO_GPRESCAN,0);
	saa_andorb(SAA7134_GPIO_GPMODE3,SAA7134_GPIO_GPRESCAN,SAA7134_GPIO_GPRESCAN);
	mode   = saa_readl(SAA7134_GPIO_GPMODE0   >> 2) & 0xfffffff;
	status = saa_readl(SAA7134_GPIO_GPSTATUS0 >> 2) & 0xfffffff;
	core_dbg("%s: gpio: mode=0x%07lx in=0x%07lx out=0x%07lx [%s]\n",
	       dev->name, mode, (~mode) & status, mode & status, msg);
}