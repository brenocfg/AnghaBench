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
struct property_set {struct property_entry* properties; } ;
struct property_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct property_set* ERR_CAST (struct property_entry*) ; 
 struct property_set* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct property_entry*) ; 
 int /*<<< orphan*/  kfree (struct property_set*) ; 
 struct property_set* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct property_entry* property_entries_dup (struct property_entry*) ; 

__attribute__((used)) static struct property_set *pset_copy_set(const struct property_set *pset)
{
	struct property_entry *properties;
	struct property_set *p;

	p = kzalloc(sizeof(*p), GFP_KERNEL);
	if (!p)
		return ERR_PTR(-ENOMEM);

	properties = property_entries_dup(pset->properties);
	if (IS_ERR(properties)) {
		kfree(p);
		return ERR_CAST(properties);
	}

	p->properties = properties;
	return p;
}