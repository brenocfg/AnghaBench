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
struct device_node {int dummy; } ;
struct device {TYPE_1__* parent; } ;
struct as3711_bl_pdata {int su1_fb; scalar_t__ su1_max_uA; int su2_fb; scalar_t__ su2_max_uA; scalar_t__ su2_feedback; int su2_auto_curr1; int su2_auto_curr2; int su2_auto_curr3; int /*<<< orphan*/  su2_fbprot; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 scalar_t__ AS3711_SU2_CURR1 ; 
 scalar_t__ AS3711_SU2_CURR2 ; 
 scalar_t__ AS3711_SU2_CURR3 ; 
 scalar_t__ AS3711_SU2_CURR_AUTO ; 
 int /*<<< orphan*/  AS3711_SU2_GPIO2 ; 
 int /*<<< orphan*/  AS3711_SU2_GPIO3 ; 
 int /*<<< orphan*/  AS3711_SU2_GPIO4 ; 
 int /*<<< orphan*/  AS3711_SU2_LX_SD4 ; 
 scalar_t__ AS3711_SU2_VOLTAGE ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 struct as3711_bl_pdata* dev_get_platdata (struct device*) ; 
 scalar_t__ of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct device_node* of_get_child_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 

__attribute__((used)) static int as3711_backlight_parse_dt(struct device *dev)
{
	struct as3711_bl_pdata *pdata = dev_get_platdata(dev);
	struct device_node *bl, *fb;
	int ret;

	bl = of_get_child_by_name(dev->parent->of_node, "backlight");
	if (!bl) {
		dev_dbg(dev, "backlight node not found\n");
		return -ENODEV;
	}

	fb = of_parse_phandle(bl, "su1-dev", 0);
	if (fb) {
		of_node_put(fb);

		pdata->su1_fb = true;

		ret = of_property_read_u32(bl, "su1-max-uA", &pdata->su1_max_uA);
		if (pdata->su1_max_uA <= 0)
			ret = -EINVAL;
		if (ret < 0)
			goto err_put_bl;
	}

	fb = of_parse_phandle(bl, "su2-dev", 0);
	if (fb) {
		int count = 0;

		of_node_put(fb);

		pdata->su2_fb = true;

		ret = of_property_read_u32(bl, "su2-max-uA", &pdata->su2_max_uA);
		if (pdata->su2_max_uA <= 0)
			ret = -EINVAL;
		if (ret < 0)
			goto err_put_bl;

		if (of_find_property(bl, "su2-feedback-voltage", NULL)) {
			pdata->su2_feedback = AS3711_SU2_VOLTAGE;
			count++;
		}
		if (of_find_property(bl, "su2-feedback-curr1", NULL)) {
			pdata->su2_feedback = AS3711_SU2_CURR1;
			count++;
		}
		if (of_find_property(bl, "su2-feedback-curr2", NULL)) {
			pdata->su2_feedback = AS3711_SU2_CURR2;
			count++;
		}
		if (of_find_property(bl, "su2-feedback-curr3", NULL)) {
			pdata->su2_feedback = AS3711_SU2_CURR3;
			count++;
		}
		if (of_find_property(bl, "su2-feedback-curr-auto", NULL)) {
			pdata->su2_feedback = AS3711_SU2_CURR_AUTO;
			count++;
		}
		if (count != 1) {
			ret = -EINVAL;
			goto err_put_bl;
		}

		count = 0;
		if (of_find_property(bl, "su2-fbprot-lx-sd4", NULL)) {
			pdata->su2_fbprot = AS3711_SU2_LX_SD4;
			count++;
		}
		if (of_find_property(bl, "su2-fbprot-gpio2", NULL)) {
			pdata->su2_fbprot = AS3711_SU2_GPIO2;
			count++;
		}
		if (of_find_property(bl, "su2-fbprot-gpio3", NULL)) {
			pdata->su2_fbprot = AS3711_SU2_GPIO3;
			count++;
		}
		if (of_find_property(bl, "su2-fbprot-gpio4", NULL)) {
			pdata->su2_fbprot = AS3711_SU2_GPIO4;
			count++;
		}
		if (count != 1) {
			ret = -EINVAL;
			goto err_put_bl;
		}

		count = 0;
		if (of_find_property(bl, "su2-auto-curr1", NULL)) {
			pdata->su2_auto_curr1 = true;
			count++;
		}
		if (of_find_property(bl, "su2-auto-curr2", NULL)) {
			pdata->su2_auto_curr2 = true;
			count++;
		}
		if (of_find_property(bl, "su2-auto-curr3", NULL)) {
			pdata->su2_auto_curr3 = true;
			count++;
		}

		/*
		 * At least one su2-auto-curr* must be specified iff
		 * AS3711_SU2_CURR_AUTO is used
		 */
		if (!count ^ (pdata->su2_feedback != AS3711_SU2_CURR_AUTO)) {
			ret = -EINVAL;
			goto err_put_bl;
		}
	}

	of_node_put(bl);

	return 0;

err_put_bl:
	of_node_put(bl);

	return ret;
}