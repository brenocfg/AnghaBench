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
struct omap_aes_dev {TYPE_2__* engine; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {int max_qlen; } ;
struct TYPE_4__ {TYPE_1__ queue; } ;

/* Variables and functions */
 struct omap_aes_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t queue_len_show(struct device *dev, struct device_attribute *attr,
			      char *buf)
{
	struct omap_aes_dev *dd = dev_get_drvdata(dev);

	return sprintf(buf, "%d\n", dd->engine->queue.max_qlen);
}