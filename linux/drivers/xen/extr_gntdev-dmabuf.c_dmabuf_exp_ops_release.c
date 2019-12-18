#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gntdev_dmabuf_priv {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  refcount; int /*<<< orphan*/  map; int /*<<< orphan*/  priv; } ;
struct TYPE_4__ {TYPE_1__ exp; } ;
struct gntdev_dmabuf {TYPE_2__ u; struct gntdev_dmabuf_priv* priv; } ;
struct dma_buf {struct gntdev_dmabuf* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmabuf_exp_release ; 
 int /*<<< orphan*/  dmabuf_exp_remove_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dmabuf_exp_ops_release(struct dma_buf *dma_buf)
{
	struct gntdev_dmabuf *gntdev_dmabuf = dma_buf->priv;
	struct gntdev_dmabuf_priv *priv = gntdev_dmabuf->priv;

	dmabuf_exp_remove_map(gntdev_dmabuf->u.exp.priv,
			      gntdev_dmabuf->u.exp.map);
	mutex_lock(&priv->lock);
	kref_put(&gntdev_dmabuf->u.exp.refcount, dmabuf_exp_release);
	mutex_unlock(&priv->lock);
}