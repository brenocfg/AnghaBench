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
struct ipu_dc_priv {int /*<<< orphan*/  mutex; } ;
struct ipu_dc {int in_use; struct ipu_dc_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void ipu_dc_put(struct ipu_dc *dc)
{
	struct ipu_dc_priv *priv = dc->priv;

	mutex_lock(&priv->mutex);
	dc->in_use = false;
	mutex_unlock(&priv->mutex);
}