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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int device_type; } ;
struct ap_card {TYPE_1__ ap_dev; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 struct ap_card* to_ap_card (struct device*) ; 

__attribute__((used)) static ssize_t hwtype_show(struct device *dev,
			   struct device_attribute *attr, char *buf)
{
	struct ap_card *ac = to_ap_card(dev);

	return snprintf(buf, PAGE_SIZE, "%d\n", ac->ap_dev.device_type);
}