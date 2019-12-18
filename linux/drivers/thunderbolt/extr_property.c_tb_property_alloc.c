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
struct tb_property {int type; int /*<<< orphan*/  list; int /*<<< orphan*/  key; } ;
typedef  enum tb_property_type { ____Placeholder_tb_property_type } tb_property_type ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct tb_property* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct tb_property *
tb_property_alloc(const char *key, enum tb_property_type type)
{
	struct tb_property *property;

	property = kzalloc(sizeof(*property), GFP_KERNEL);
	if (!property)
		return NULL;

	strcpy(property->key, key);
	property->type = type;
	INIT_LIST_HEAD(&property->list);

	return property;
}