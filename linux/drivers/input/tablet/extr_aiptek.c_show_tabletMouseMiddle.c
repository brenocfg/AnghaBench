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
struct TYPE_2__ {int /*<<< orphan*/  mouseButtonMiddle; } ;
struct aiptek {TYPE_1__ curSetting; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct aiptek* dev_get_drvdata (struct device*) ; 
 char* map_val_to_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mouse_button_map ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static ssize_t show_tabletMouseMiddle(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct aiptek *aiptek = dev_get_drvdata(dev);

	return snprintf(buf, PAGE_SIZE, "%s\n",
			map_val_to_str(mouse_button_map,
					aiptek->curSetting.mouseButtonMiddle));
}