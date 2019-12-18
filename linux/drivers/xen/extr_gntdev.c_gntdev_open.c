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
struct inode {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ops; } ;
struct gntdev_priv {int /*<<< orphan*/  dma_dev; int /*<<< orphan*/  mm; TYPE_1__ mn; int /*<<< orphan*/  dmabuf_priv; int /*<<< orphan*/  lock; int /*<<< orphan*/  freeable_maps; int /*<<< orphan*/  maps; } ;
struct file {struct gntdev_priv* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  this_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dma_coerce_mask_and_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_task_mm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gntdev_dmabuf_init (struct file*) ; 
 TYPE_2__ gntdev_miscdev ; 
 int /*<<< orphan*/  gntdev_mmu_ops ; 
 int /*<<< orphan*/  kfree (struct gntdev_priv*) ; 
 struct gntdev_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmput (int /*<<< orphan*/ ) ; 
 int mmu_notifier_register (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,struct gntdev_priv*) ; 
 scalar_t__ use_ptemod ; 

__attribute__((used)) static int gntdev_open(struct inode *inode, struct file *flip)
{
	struct gntdev_priv *priv;
	int ret = 0;

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	INIT_LIST_HEAD(&priv->maps);
	INIT_LIST_HEAD(&priv->freeable_maps);
	mutex_init(&priv->lock);

#ifdef CONFIG_XEN_GNTDEV_DMABUF
	priv->dmabuf_priv = gntdev_dmabuf_init(flip);
	if (IS_ERR(priv->dmabuf_priv)) {
		ret = PTR_ERR(priv->dmabuf_priv);
		kfree(priv);
		return ret;
	}
#endif

	if (use_ptemod) {
		priv->mm = get_task_mm(current);
		if (!priv->mm) {
			kfree(priv);
			return -ENOMEM;
		}
		priv->mn.ops = &gntdev_mmu_ops;
		ret = mmu_notifier_register(&priv->mn, priv->mm);
		mmput(priv->mm);
	}

	if (ret) {
		kfree(priv);
		return ret;
	}

	flip->private_data = priv;
#ifdef CONFIG_XEN_GRANT_DMA_ALLOC
	priv->dma_dev = gntdev_miscdev.this_device;
	dma_coerce_mask_and_coherent(priv->dma_dev, DMA_BIT_MASK(64));
#endif
	pr_debug("priv %p\n", priv);

	return 0;
}