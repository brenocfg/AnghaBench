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
typedef  unsigned int uint32_t ;
struct vmw_private {int /*<<< orphan*/  hw_lock; scalar_t__ io_start; } ;

/* Variables and functions */
 scalar_t__ VMWGFX_INDEX_PORT ; 
 scalar_t__ VMWGFX_VALUE_PORT ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void vmw_write(struct vmw_private *dev_priv,
			     unsigned int offset, uint32_t value)
{
	spin_lock(&dev_priv->hw_lock);
	outl(offset, dev_priv->io_start + VMWGFX_INDEX_PORT);
	outl(value, dev_priv->io_start + VMWGFX_VALUE_PORT);
	spin_unlock(&dev_priv->hw_lock);
}