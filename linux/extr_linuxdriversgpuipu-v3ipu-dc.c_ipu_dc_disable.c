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
struct ipu_soc {struct ipu_dc_priv* dc_priv; } ;
struct ipu_dc_priv {scalar_t__ use_count; int /*<<< orphan*/  mutex; int /*<<< orphan*/  ipu; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPU_CONF_DC_EN ; 
 int /*<<< orphan*/  ipu_module_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void ipu_dc_disable(struct ipu_soc *ipu)
{
	struct ipu_dc_priv *priv = ipu->dc_priv;

	mutex_lock(&priv->mutex);

	priv->use_count--;
	if (!priv->use_count)
		ipu_module_disable(priv->ipu, IPU_CONF_DC_EN);

	if (priv->use_count < 0)
		priv->use_count = 0;

	mutex_unlock(&priv->mutex);
}