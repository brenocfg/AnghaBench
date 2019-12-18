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
struct reset_control {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct reset_control* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct reset_control*) ; 
 struct reset_control* __reset_control_get (struct device*,char const*,int,int,int,int) ; 
 int /*<<< orphan*/  devm_reset_control_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct reset_control**) ; 
 struct reset_control** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct reset_control**) ; 

struct reset_control *__devm_reset_control_get(struct device *dev,
				     const char *id, int index, bool shared,
				     bool optional, bool acquired)
{
	struct reset_control **ptr, *rstc;

	ptr = devres_alloc(devm_reset_control_release, sizeof(*ptr),
			   GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	rstc = __reset_control_get(dev, id, index, shared, optional, acquired);
	if (!IS_ERR(rstc)) {
		*ptr = rstc;
		devres_add(dev, ptr);
	} else {
		devres_free(ptr);
	}

	return rstc;
}