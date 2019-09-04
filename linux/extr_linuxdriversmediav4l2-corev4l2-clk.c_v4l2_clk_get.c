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
struct v4l2_clk {int /*<<< orphan*/  use_count; struct v4l2_clk* clk; } ;
struct device {scalar_t__ of_node; } ;
struct clk {int /*<<< orphan*/  use_count; struct clk* clk; } ;
typedef  int /*<<< orphan*/  clk_name ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct v4l2_clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct v4l2_clk*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct v4l2_clk*) ; 
 int /*<<< orphan*/  PTR_ERR (struct v4l2_clk*) ; 
 int V4L2_CLK_NAME_SIZE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct v4l2_clk* clk_get (struct device*,char const*) ; 
 int /*<<< orphan*/  clk_lock ; 
 int /*<<< orphan*/  clk_put (struct v4l2_clk*) ; 
 char* dev_name (struct device*) ; 
 struct v4l2_clk* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct v4l2_clk* v4l2_clk_find (char*) ; 
 int /*<<< orphan*/  v4l2_clk_name_of (char*,int,scalar_t__) ; 

struct v4l2_clk *v4l2_clk_get(struct device *dev, const char *id)
{
	struct v4l2_clk *clk;
	struct clk *ccf_clk = clk_get(dev, id);
	char clk_name[V4L2_CLK_NAME_SIZE];

	if (PTR_ERR(ccf_clk) == -EPROBE_DEFER)
		return ERR_PTR(-EPROBE_DEFER);

	if (!IS_ERR_OR_NULL(ccf_clk)) {
		clk = kzalloc(sizeof(*clk), GFP_KERNEL);
		if (!clk) {
			clk_put(ccf_clk);
			return ERR_PTR(-ENOMEM);
		}
		clk->clk = ccf_clk;

		return clk;
	}

	mutex_lock(&clk_lock);
	clk = v4l2_clk_find(dev_name(dev));

	/* if dev_name is not found, try use the OF name to find again  */
	if (PTR_ERR(clk) == -ENODEV && dev->of_node) {
		v4l2_clk_name_of(clk_name, sizeof(clk_name), dev->of_node);
		clk = v4l2_clk_find(clk_name);
	}

	if (!IS_ERR(clk))
		atomic_inc(&clk->use_count);
	mutex_unlock(&clk_lock);

	return clk;
}