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
struct encx24j600_priv {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int encx24j600_soft_reset (struct encx24j600_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int encx24j600_hw_reset(struct encx24j600_priv *priv)
{
	int ret;

	mutex_lock(&priv->lock);
	ret = encx24j600_soft_reset(priv);
	mutex_unlock(&priv->lock);

	return ret;
}