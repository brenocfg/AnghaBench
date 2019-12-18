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
struct gpio_desc {int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VALIDATE_DESC (struct gpio_desc*) ; 
 int /*<<< orphan*/  desc_set_label (struct gpio_desc*,char const*) ; 
 int /*<<< orphan*/  kfree_const (int /*<<< orphan*/ ) ; 
 char* kstrdup_const (char const*,int /*<<< orphan*/ ) ; 

int gpiod_set_consumer_name(struct gpio_desc *desc, const char *name)
{
	VALIDATE_DESC(desc);
	if (name) {
		name = kstrdup_const(name, GFP_KERNEL);
		if (!name)
			return -ENOMEM;
	}

	kfree_const(desc->label);
	desc_set_label(desc, name);

	return 0;
}