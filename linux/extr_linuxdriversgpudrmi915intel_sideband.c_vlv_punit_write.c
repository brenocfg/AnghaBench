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
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {int /*<<< orphan*/  sb_lock; int /*<<< orphan*/  pcu_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOSF_PORT_PUNIT ; 
 int /*<<< orphan*/  PCI_DEVFN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SB_CRWRDA_NP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vlv_sideband_rw (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int vlv_punit_write(struct drm_i915_private *dev_priv, u32 addr, u32 val)
{
	int err;

	WARN_ON(!mutex_is_locked(&dev_priv->pcu_lock));

	mutex_lock(&dev_priv->sb_lock);
	err = vlv_sideband_rw(dev_priv, PCI_DEVFN(0, 0), IOSF_PORT_PUNIT,
			      SB_CRWRDA_NP, addr, &val);
	mutex_unlock(&dev_priv->sb_lock);

	return err;
}