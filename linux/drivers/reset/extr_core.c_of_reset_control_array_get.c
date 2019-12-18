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
struct reset_control {int array; } ;
struct reset_control_array {int num_rstcs; struct reset_control** rstc; struct reset_control base; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct reset_control* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct reset_control*) ; 
 struct reset_control* __of_reset_control_get (struct device_node*,int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  __reset_control_put_internal (struct reset_control*) ; 
 int /*<<< orphan*/  kfree (struct reset_control_array*) ; 
 struct reset_control_array* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int of_reset_control_get_count (struct device_node*) ; 
 int /*<<< orphan*/  reset_list_mutex ; 
 int /*<<< orphan*/  struct_size (struct reset_control_array*,struct reset_control*,int) ; 

struct reset_control *
of_reset_control_array_get(struct device_node *np, bool shared, bool optional,
			   bool acquired)
{
	struct reset_control_array *resets;
	struct reset_control *rstc;
	int num, i;

	num = of_reset_control_get_count(np);
	if (num < 0)
		return optional ? NULL : ERR_PTR(num);

	resets = kzalloc(struct_size(resets, rstc, num), GFP_KERNEL);
	if (!resets)
		return ERR_PTR(-ENOMEM);

	for (i = 0; i < num; i++) {
		rstc = __of_reset_control_get(np, NULL, i, shared, optional,
					      acquired);
		if (IS_ERR(rstc))
			goto err_rst;
		resets->rstc[i] = rstc;
	}
	resets->num_rstcs = num;
	resets->base.array = true;

	return &resets->base;

err_rst:
	mutex_lock(&reset_list_mutex);
	while (--i >= 0)
		__reset_control_put_internal(resets->rstc[i]);
	mutex_unlock(&reset_list_mutex);

	kfree(resets);

	return rstc;
}