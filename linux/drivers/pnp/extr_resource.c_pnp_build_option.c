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
struct pnp_option {unsigned int flags; unsigned long type; int /*<<< orphan*/  list; } ;
struct pnp_dev {int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct pnp_option* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct pnp_option *pnp_build_option(struct pnp_dev *dev, unsigned long type,
				    unsigned int option_flags)
{
	struct pnp_option *option;

	option = kzalloc(sizeof(struct pnp_option), GFP_KERNEL);
	if (!option)
		return NULL;

	option->flags = option_flags;
	option->type = type;

	list_add_tail(&option->list, &dev->options);
	return option;
}