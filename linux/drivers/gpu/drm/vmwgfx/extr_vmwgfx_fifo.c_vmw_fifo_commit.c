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
typedef  int /*<<< orphan*/  uint32_t ;
struct vmw_private {scalar_t__ cman; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmw_cmdbuf_commit (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vmw_local_fifo_commit (struct vmw_private*,int /*<<< orphan*/ ) ; 

void vmw_fifo_commit(struct vmw_private *dev_priv, uint32_t bytes)
{
	if (dev_priv->cman)
		vmw_cmdbuf_commit(dev_priv->cman, bytes, NULL, false);
	else
		vmw_local_fifo_commit(dev_priv, bytes);
}