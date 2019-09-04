#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sensor_template_group {scalar_t__ base; struct sensor_device_template** templates; int /*<<< orphan*/  is_visible; } ;
struct TYPE_12__ {char* name; int /*<<< orphan*/  mode; } ;
struct TYPE_13__ {int /*<<< orphan*/  store; int /*<<< orphan*/  show; TYPE_5__ attr; } ;
struct TYPE_8__ {int /*<<< orphan*/  index; scalar_t__ nr; } ;
struct TYPE_11__ {scalar_t__ index; TYPE_1__ s; } ;
struct sensor_device_template {TYPE_6__ dev_attr; TYPE_4__ u; scalar_t__ s2; } ;
struct attribute {int /*<<< orphan*/  mode; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {struct attribute attr; int /*<<< orphan*/  store; int /*<<< orphan*/  show; } ;
struct sensor_device_attribute_2 {TYPE_2__ dev_attr; int /*<<< orphan*/  index; scalar_t__ nr; } ;
struct TYPE_14__ {struct attribute attr; int /*<<< orphan*/  store; int /*<<< orphan*/  show; } ;
struct sensor_device_attribute {TYPE_7__ dev_attr; scalar_t__ index; } ;
struct TYPE_10__ {struct sensor_device_attribute a1; struct sensor_device_attribute_2 a2; } ;
struct sensor_device_attr_u {int /*<<< orphan*/  name; TYPE_3__ u; } ;
struct device {int dummy; } ;
struct attribute_group {int /*<<< orphan*/  is_visible; struct attribute** attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct attribute_group* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int array3_size (int,int,int) ; 
 struct attribute** devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  sysfs_attr_init (struct attribute*) ; 

__attribute__((used)) static struct attribute_group *
nct6775_create_attr_group(struct device *dev,
			  const struct sensor_template_group *tg,
			  int repeat)
{
	struct attribute_group *group;
	struct sensor_device_attr_u *su;
	struct sensor_device_attribute *a;
	struct sensor_device_attribute_2 *a2;
	struct attribute **attrs;
	struct sensor_device_template **t;
	int i, count;

	if (repeat <= 0)
		return ERR_PTR(-EINVAL);

	t = tg->templates;
	for (count = 0; *t; t++, count++)
		;

	if (count == 0)
		return ERR_PTR(-EINVAL);

	group = devm_kzalloc(dev, sizeof(*group), GFP_KERNEL);
	if (group == NULL)
		return ERR_PTR(-ENOMEM);

	attrs = devm_kcalloc(dev, repeat * count + 1, sizeof(*attrs),
			     GFP_KERNEL);
	if (attrs == NULL)
		return ERR_PTR(-ENOMEM);

	su = devm_kzalloc(dev, array3_size(repeat, count, sizeof(*su)),
			       GFP_KERNEL);
	if (su == NULL)
		return ERR_PTR(-ENOMEM);

	group->attrs = attrs;
	group->is_visible = tg->is_visible;

	for (i = 0; i < repeat; i++) {
		t = tg->templates;
		while (*t != NULL) {
			snprintf(su->name, sizeof(su->name),
				 (*t)->dev_attr.attr.name, tg->base + i);
			if ((*t)->s2) {
				a2 = &su->u.a2;
				sysfs_attr_init(&a2->dev_attr.attr);
				a2->dev_attr.attr.name = su->name;
				a2->nr = (*t)->u.s.nr + i;
				a2->index = (*t)->u.s.index;
				a2->dev_attr.attr.mode =
				  (*t)->dev_attr.attr.mode;
				a2->dev_attr.show = (*t)->dev_attr.show;
				a2->dev_attr.store = (*t)->dev_attr.store;
				*attrs = &a2->dev_attr.attr;
			} else {
				a = &su->u.a1;
				sysfs_attr_init(&a->dev_attr.attr);
				a->dev_attr.attr.name = su->name;
				a->index = (*t)->u.index + i;
				a->dev_attr.attr.mode =
				  (*t)->dev_attr.attr.mode;
				a->dev_attr.show = (*t)->dev_attr.show;
				a->dev_attr.store = (*t)->dev_attr.store;
				*attrs = &a->dev_attr.attr;
			}
			attrs++;
			su++;
			t++;
		}
	}

	return group;
}