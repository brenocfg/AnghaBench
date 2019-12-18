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
struct prp_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  vdev; int /*<<< orphan*/  eof_timeout_timer; int /*<<< orphan*/  irqlock; struct imx_ic_priv* ic_priv; } ;
struct imx_ic_priv {int /*<<< orphan*/  sd; int /*<<< orphan*/  ipu_dev; struct prp_priv* task_priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRPENCVF_SRC_PAD ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct prp_priv* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_media_capture_device_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prp_eof_timeout ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prp_init(struct imx_ic_priv *ic_priv)
{
	struct prp_priv *priv;

	priv = devm_kzalloc(ic_priv->ipu_dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	ic_priv->task_priv = priv;
	priv->ic_priv = ic_priv;

	spin_lock_init(&priv->irqlock);
	timer_setup(&priv->eof_timeout_timer, prp_eof_timeout, 0);

	priv->vdev = imx_media_capture_device_init(ic_priv->ipu_dev,
						   &ic_priv->sd,
						   PRPENCVF_SRC_PAD);
	if (IS_ERR(priv->vdev))
		return PTR_ERR(priv->vdev);

	mutex_init(&priv->lock);

	return 0;
}