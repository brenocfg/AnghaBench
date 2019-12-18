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
struct gntdev_dmabuf_wait_obj {int /*<<< orphan*/  next; } ;
struct gntdev_dmabuf_priv {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct gntdev_dmabuf_wait_obj*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dmabuf_exp_wait_obj_free(struct gntdev_dmabuf_priv *priv,
				     struct gntdev_dmabuf_wait_obj *obj)
{
	mutex_lock(&priv->lock);
	list_del(&obj->next);
	mutex_unlock(&priv->lock);
	kfree(obj);
}