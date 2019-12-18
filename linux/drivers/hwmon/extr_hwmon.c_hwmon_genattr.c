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
typedef  int umode_t ;
typedef  int /*<<< orphan*/  u32 ;
struct hwmon_ops {int (* is_visible ) (void const*,int,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  read_string; } ;
struct attribute {char const* name; int mode; } ;
struct device_attribute {struct attribute attr; int /*<<< orphan*/  store; int /*<<< orphan*/  show; } ;
struct hwmon_device_attribute {char* name; int type; int index; struct device_attribute dev_attr; struct hwmon_ops const* ops; int /*<<< orphan*/  attr; } ;
struct device {int dummy; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct attribute* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct hwmon_device_attribute* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ hwmon_attr_base (int) ; 
 int /*<<< orphan*/  hwmon_attr_show ; 
 int /*<<< orphan*/  hwmon_attr_show_string ; 
 int /*<<< orphan*/  hwmon_attr_store ; 
 int hwmon_chip ; 
 int is_string_attr (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char const*,scalar_t__) ; 
 int stub1 (void const*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sysfs_attr_init (struct attribute*) ; 

__attribute__((used)) static struct attribute *hwmon_genattr(struct device *dev,
				       const void *drvdata,
				       enum hwmon_sensor_types type,
				       u32 attr,
				       int index,
				       const char *template,
				       const struct hwmon_ops *ops)
{
	struct hwmon_device_attribute *hattr;
	struct device_attribute *dattr;
	struct attribute *a;
	umode_t mode;
	const char *name;
	bool is_string = is_string_attr(type, attr);

	/* The attribute is invisible if there is no template string */
	if (!template)
		return ERR_PTR(-ENOENT);

	mode = ops->is_visible(drvdata, type, attr, index);
	if (!mode)
		return ERR_PTR(-ENOENT);

	if ((mode & 0444) && ((is_string && !ops->read_string) ||
				 (!is_string && !ops->read)))
		return ERR_PTR(-EINVAL);
	if ((mode & 0222) && !ops->write)
		return ERR_PTR(-EINVAL);

	hattr = devm_kzalloc(dev, sizeof(*hattr), GFP_KERNEL);
	if (!hattr)
		return ERR_PTR(-ENOMEM);

	if (type == hwmon_chip) {
		name = template;
	} else {
		scnprintf(hattr->name, sizeof(hattr->name), template,
			  index + hwmon_attr_base(type));
		name = hattr->name;
	}

	hattr->type = type;
	hattr->attr = attr;
	hattr->index = index;
	hattr->ops = ops;

	dattr = &hattr->dev_attr;
	dattr->show = is_string ? hwmon_attr_show_string : hwmon_attr_show;
	dattr->store = hwmon_attr_store;

	a = &dattr->attr;
	sysfs_attr_init(a);
	a->name = name;
	a->mode = mode;

	return a;
}