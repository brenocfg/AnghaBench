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
typedef  int u32 ;
struct property {int length; struct property* value; struct property* name; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  be32_to_cpu (int) ; 
 int cxl_update_properties (struct device_node*,struct property*) ; 
 int /*<<< orphan*/  kfree (struct property*) ; 
 struct property* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct property*,char*,int) ; 
 int /*<<< orphan*/  pr_devel (char*,struct device_node*,char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int update_property(struct device_node *dn, const char *name,
			   u32 vd, char *value)
{
	struct property *new_prop;
	u32 *val;
	int rc;

	new_prop = kzalloc(sizeof(*new_prop), GFP_KERNEL);
	if (!new_prop)
		return -ENOMEM;

	new_prop->name = kstrdup(name, GFP_KERNEL);
	if (!new_prop->name) {
		kfree(new_prop);
		return -ENOMEM;
	}

	new_prop->length = vd;
	new_prop->value = kzalloc(new_prop->length, GFP_KERNEL);
	if (!new_prop->value) {
		kfree(new_prop->name);
		kfree(new_prop);
		return -ENOMEM;
	}
	memcpy(new_prop->value, value, vd);

	val = (u32 *)new_prop->value;
	rc = cxl_update_properties(dn, new_prop);
	pr_devel("%pOFn: update property (%s, length: %i, value: %#x)\n",
		  dn, name, vd, be32_to_cpu(*val));

	if (rc) {
		kfree(new_prop->name);
		kfree(new_prop->value);
		kfree(new_prop);
	}
	return rc;
}