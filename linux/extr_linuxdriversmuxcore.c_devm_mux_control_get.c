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
struct mux_control {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct mux_control* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mux_control*) ; 
 int /*<<< orphan*/  devm_mux_control_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct mux_control**) ; 
 struct mux_control** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct mux_control**) ; 
 struct mux_control* mux_control_get (struct device*,char const*) ; 

struct mux_control *devm_mux_control_get(struct device *dev,
					 const char *mux_name)
{
	struct mux_control **ptr, *mux;

	ptr = devres_alloc(devm_mux_control_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	mux = mux_control_get(dev, mux_name);
	if (IS_ERR(mux)) {
		devres_free(ptr);
		return mux;
	}

	*ptr = mux;
	devres_add(dev, ptr);

	return mux;
}