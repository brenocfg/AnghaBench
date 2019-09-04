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
struct uld_ctx {int /*<<< orphan*/  entry; struct chcr_dev* dev; } ;
struct chcr_dev {struct uld_ctx* u_ctx; int /*<<< orphan*/  lock_chcr_dev; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct uld_ctx* ctx_rr ; 
 int /*<<< orphan*/  dev_count ; 
 int /*<<< orphan*/  dev_mutex ; 
 struct chcr_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uld_ctx_list ; 

__attribute__((used)) static int chcr_dev_add(struct uld_ctx *u_ctx)
{
	struct chcr_dev *dev;

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENXIO;

	spin_lock_init(&dev->lock_chcr_dev);
	u_ctx->dev = dev;
	dev->u_ctx = u_ctx;
	atomic_inc(&dev_count);
	mutex_lock(&dev_mutex);
	list_add_tail(&u_ctx->entry, &uld_ctx_list);
	if (!ctx_rr)
		ctx_rr = u_ctx;
	mutex_unlock(&dev_mutex);
	return 0;
}