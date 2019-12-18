#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  size_t u8 ;
struct platform_zone {int dummy; } ;
struct TYPE_18__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_8__ dev; } ;
struct device_attribute {int dummy; } ;
struct attribute {int dummy; } ;
struct TYPE_19__ {int max_brightness; } ;
struct TYPE_17__ {int num_zones; } ;
struct TYPE_16__ {TYPE_3__** attrs; } ;
struct TYPE_15__ {char* name; int mode; } ;
struct TYPE_14__ {size_t location; TYPE_1__* attr; } ;
struct TYPE_13__ {TYPE_3__ attr; int /*<<< orphan*/  store; int /*<<< orphan*/  show; } ;
struct TYPE_12__ {TYPE_3__ attr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ LEGACY ; 
 int /*<<< orphan*/  LEGACY_RUNNING ; 
 scalar_t__ WMAX ; 
 int /*<<< orphan*/  WMAX_RUNNING ; 
 TYPE_11__ dev_attr_lighting_control_state ; 
 int global_brightness ; 
 TYPE_9__ global_led ; 
 scalar_t__ interface ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_classdev_register (TYPE_8__*,TYPE_9__*) ; 
 int /*<<< orphan*/  lighting_control_state ; 
 TYPE_7__* quirks ; 
 int /*<<< orphan*/  sprintf (char*,char*,size_t) ; 
 int /*<<< orphan*/  sysfs_attr_init (TYPE_3__*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_4__ zone_attribute_group ; 
 TYPE_3__** zone_attrs ; 
 TYPE_2__* zone_data ; 
 TYPE_1__* zone_dev_attrs ; 
 int /*<<< orphan*/  zone_set ; 
 int /*<<< orphan*/  zone_show ; 

__attribute__((used)) static int alienware_zone_init(struct platform_device *dev)
{
	u8 zone;
	char buffer[10];
	char *name;

	if (interface == WMAX) {
		lighting_control_state = WMAX_RUNNING;
	} else if (interface == LEGACY) {
		lighting_control_state = LEGACY_RUNNING;
	}
	global_led.max_brightness = 0x0F;
	global_brightness = global_led.max_brightness;

	/*
	 *      - zone_dev_attrs num_zones + 1 is for individual zones and then
	 *        null terminated
	 *      - zone_attrs num_zones + 2 is for all attrs in zone_dev_attrs +
	 *        the lighting control + null terminated
	 *      - zone_data num_zones is for the distinct zones
	 */
	zone_dev_attrs =
	    kcalloc(quirks->num_zones + 1, sizeof(struct device_attribute),
		    GFP_KERNEL);
	if (!zone_dev_attrs)
		return -ENOMEM;

	zone_attrs =
	    kcalloc(quirks->num_zones + 2, sizeof(struct attribute *),
		    GFP_KERNEL);
	if (!zone_attrs)
		return -ENOMEM;

	zone_data =
	    kcalloc(quirks->num_zones, sizeof(struct platform_zone),
		    GFP_KERNEL);
	if (!zone_data)
		return -ENOMEM;

	for (zone = 0; zone < quirks->num_zones; zone++) {
		sprintf(buffer, "zone%02hhX", zone);
		name = kstrdup(buffer, GFP_KERNEL);
		if (name == NULL)
			return 1;
		sysfs_attr_init(&zone_dev_attrs[zone].attr);
		zone_dev_attrs[zone].attr.name = name;
		zone_dev_attrs[zone].attr.mode = 0644;
		zone_dev_attrs[zone].show = zone_show;
		zone_dev_attrs[zone].store = zone_set;
		zone_data[zone].location = zone;
		zone_attrs[zone] = &zone_dev_attrs[zone].attr;
		zone_data[zone].attr = &zone_dev_attrs[zone];
	}
	zone_attrs[quirks->num_zones] = &dev_attr_lighting_control_state.attr;
	zone_attribute_group.attrs = zone_attrs;

	led_classdev_register(&dev->dev, &global_led);

	return sysfs_create_group(&dev->dev.kobj, &zone_attribute_group);
}