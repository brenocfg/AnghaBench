#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct trackpoint_data {scalar_t__ variant_id; } ;
struct psmouse {struct trackpoint_data* private; } ;
struct attribute {int dummy; } ;
struct TYPE_6__ {struct attribute attr; } ;
struct TYPE_8__ {TYPE_2__ dattr; } ;
struct TYPE_5__ {struct attribute attr; } ;
struct TYPE_7__ {TYPE_1__ dattr; } ;

/* Variables and functions */
 scalar_t__ TP_VARIANT_IBM ; 
 TYPE_4__ psmouse_attr_press_to_select ; 
 TYPE_3__ psmouse_attr_sensitivity ; 

__attribute__((used)) static bool trackpoint_is_attr_available(struct psmouse *psmouse,
					 struct attribute *attr)
{
	struct trackpoint_data *tp = psmouse->private;

	return tp->variant_id == TP_VARIANT_IBM ||
		attr == &psmouse_attr_sensitivity.dattr.attr ||
		attr == &psmouse_attr_press_to_select.dattr.attr;
}