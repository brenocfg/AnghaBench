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
struct zcrypt_card {int /*<<< orphan*/  load; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {struct zcrypt_card* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* to_ap_card (struct device*) ; 

__attribute__((used)) static ssize_t load_show(struct device *dev,
			 struct device_attribute *attr,
			 char *buf)
{
	struct zcrypt_card *zc = to_ap_card(dev)->private;

	return snprintf(buf, PAGE_SIZE, "%d\n", atomic_read(&zc->load));
}