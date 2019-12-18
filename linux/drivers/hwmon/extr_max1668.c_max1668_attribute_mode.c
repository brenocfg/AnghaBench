#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_20__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_19__ ;
typedef  struct TYPE_29__   TYPE_18__ ;
typedef  struct TYPE_28__   TYPE_17__ ;
typedef  struct TYPE_27__   TYPE_16__ ;
typedef  struct TYPE_26__   TYPE_15__ ;
typedef  struct TYPE_25__   TYPE_14__ ;
typedef  struct TYPE_24__   TYPE_13__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  umode_t ;
struct kobject {int dummy; } ;
struct attribute {int dummy; } ;
struct TYPE_40__ {struct attribute attr; } ;
struct TYPE_39__ {struct attribute attr; } ;
struct TYPE_38__ {struct attribute attr; } ;
struct TYPE_37__ {struct attribute attr; } ;
struct TYPE_36__ {struct attribute attr; } ;
struct TYPE_35__ {struct attribute attr; } ;
struct TYPE_34__ {struct attribute attr; } ;
struct TYPE_33__ {struct attribute attr; } ;
struct TYPE_31__ {struct attribute attr; } ;
struct TYPE_32__ {TYPE_1__ dev_attr; } ;
struct TYPE_30__ {TYPE_6__ dev_attr; } ;
struct TYPE_29__ {TYPE_2__ dev_attr; } ;
struct TYPE_28__ {TYPE_7__ dev_attr; } ;
struct TYPE_27__ {TYPE_3__ dev_attr; } ;
struct TYPE_26__ {TYPE_8__ dev_attr; } ;
struct TYPE_25__ {TYPE_4__ dev_attr; } ;
struct TYPE_24__ {TYPE_9__ dev_attr; } ;
struct TYPE_23__ {TYPE_5__ dev_attr; } ;
struct TYPE_21__ {struct attribute attr; } ;
struct TYPE_22__ {TYPE_10__ dev_attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  S_IWUSR ; 
 scalar_t__ read_only ; 
 TYPE_20__ sensor_dev_attr_temp1_max ; 
 TYPE_19__ sensor_dev_attr_temp1_min ; 
 TYPE_18__ sensor_dev_attr_temp2_max ; 
 TYPE_17__ sensor_dev_attr_temp2_min ; 
 TYPE_16__ sensor_dev_attr_temp3_max ; 
 TYPE_15__ sensor_dev_attr_temp3_min ; 
 TYPE_14__ sensor_dev_attr_temp4_max ; 
 TYPE_13__ sensor_dev_attr_temp4_min ; 
 TYPE_12__ sensor_dev_attr_temp5_max ; 
 TYPE_11__ sensor_dev_attr_temp5_min ; 

__attribute__((used)) static umode_t max1668_attribute_mode(struct kobject *kobj,
				     struct attribute *attr, int index)
{
	umode_t ret = S_IRUGO;
	if (read_only)
		return ret;
	if (attr == &sensor_dev_attr_temp1_max.dev_attr.attr ||
	    attr == &sensor_dev_attr_temp2_max.dev_attr.attr ||
	    attr == &sensor_dev_attr_temp3_max.dev_attr.attr ||
	    attr == &sensor_dev_attr_temp4_max.dev_attr.attr ||
	    attr == &sensor_dev_attr_temp5_max.dev_attr.attr ||
	    attr == &sensor_dev_attr_temp1_min.dev_attr.attr ||
	    attr == &sensor_dev_attr_temp2_min.dev_attr.attr ||
	    attr == &sensor_dev_attr_temp3_min.dev_attr.attr ||
	    attr == &sensor_dev_attr_temp4_min.dev_attr.attr ||
	    attr == &sensor_dev_attr_temp5_min.dev_attr.attr)
		ret |= S_IWUSR;
	return ret;
}