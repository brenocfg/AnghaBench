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
struct v4l2_clk_ops {int dummy; } ;
struct v4l2_clk {struct v4l2_clk* dev_id; int /*<<< orphan*/  list; int /*<<< orphan*/  lock; int /*<<< orphan*/  use_count; void* priv; struct v4l2_clk_ops const* ops; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct v4l2_clk* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_list ; 
 int /*<<< orphan*/  clk_lock ; 
 int /*<<< orphan*/  kfree (struct v4l2_clk*) ; 
 struct v4l2_clk* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 struct v4l2_clk* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_clk_find (char const*) ; 

struct v4l2_clk *v4l2_clk_register(const struct v4l2_clk_ops *ops,
				   const char *dev_id,
				   void *priv)
{
	struct v4l2_clk *clk;
	int ret;

	if (!ops || !dev_id)
		return ERR_PTR(-EINVAL);

	clk = kzalloc(sizeof(struct v4l2_clk), GFP_KERNEL);
	if (!clk)
		return ERR_PTR(-ENOMEM);

	clk->dev_id = kstrdup(dev_id, GFP_KERNEL);
	if (!clk->dev_id) {
		ret = -ENOMEM;
		goto ealloc;
	}
	clk->ops = ops;
	clk->priv = priv;
	atomic_set(&clk->use_count, 0);
	mutex_init(&clk->lock);

	mutex_lock(&clk_lock);
	if (!IS_ERR(v4l2_clk_find(dev_id))) {
		mutex_unlock(&clk_lock);
		ret = -EEXIST;
		goto eexist;
	}
	list_add_tail(&clk->list, &clk_list);
	mutex_unlock(&clk_lock);

	return clk;

eexist:
ealloc:
	kfree(clk->dev_id);
	kfree(clk);
	return ERR_PTR(ret);
}