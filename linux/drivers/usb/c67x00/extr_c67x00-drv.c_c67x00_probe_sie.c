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
struct c67x00_sie {int sie_num; int mode; struct c67x00_device* dev; int /*<<< orphan*/  lock; } ;
struct c67x00_device {TYPE_1__* pdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  sie_config; } ;

/* Variables and functions */
#define  C67X00_SIE_HOST 129 
#define  C67X00_SIE_UNUSED 128 
 int /*<<< orphan*/  c67x00_hcd_probe (struct c67x00_sie*) ; 
 int c67x00_sie_config (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sie_dev (struct c67x00_sie*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void c67x00_probe_sie(struct c67x00_sie *sie,
			     struct c67x00_device *dev, int sie_num)
{
	spin_lock_init(&sie->lock);
	sie->dev = dev;
	sie->sie_num = sie_num;
	sie->mode = c67x00_sie_config(dev->pdata->sie_config, sie_num);

	switch (sie->mode) {
	case C67X00_SIE_HOST:
		c67x00_hcd_probe(sie);
		break;

	case C67X00_SIE_UNUSED:
		dev_info(sie_dev(sie),
			 "Not using SIE %d as requested\n", sie->sie_num);
		break;

	default:
		dev_err(sie_dev(sie),
			"Unsupported configuration: 0x%x for SIE %d\n",
			sie->mode, sie->sie_num);
		break;
	}
}