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
struct vmw_private {int /*<<< orphan*/  reservation_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  __vmw_svga_enable (struct vmw_private*) ; 
 int /*<<< orphan*/  ttm_read_lock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ttm_read_unlock (int /*<<< orphan*/ *) ; 

void vmw_svga_enable(struct vmw_private *dev_priv)
{
	(void) ttm_read_lock(&dev_priv->reservation_sem, false);
	__vmw_svga_enable(dev_priv);
	ttm_read_unlock(&dev_priv->reservation_sem);
}