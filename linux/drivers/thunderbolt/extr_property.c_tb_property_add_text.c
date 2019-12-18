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
struct tb_property_dir {int /*<<< orphan*/  properties; } ;
struct TYPE_2__ {int /*<<< orphan*/  text; } ;
struct tb_property {size_t length; int /*<<< orphan*/  list; TYPE_1__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TB_PROPERTY_TYPE_TEXT ; 
 int /*<<< orphan*/  kfree (struct tb_property*) ; 
 int /*<<< orphan*/  kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t round_up (scalar_t__,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 struct tb_property* tb_property_alloc (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_property_key_valid (char const*) ; 

int tb_property_add_text(struct tb_property_dir *parent, const char *key,
			 const char *text)
{
	/* Need to pad to dword boundary */
	size_t size = round_up(strlen(text) + 1, 4);
	struct tb_property *property;

	if (!tb_property_key_valid(key))
		return -EINVAL;

	property = tb_property_alloc(key, TB_PROPERTY_TYPE_TEXT);
	if (!property)
		return -ENOMEM;

	property->length = size / 4;
	property->value.text = kzalloc(size, GFP_KERNEL);
	if (!property->value.text) {
		kfree(property);
		return -ENOMEM;
	}

	strcpy(property->value.text, text);

	list_add_tail(&property->list, &parent->properties);
	return 0;
}