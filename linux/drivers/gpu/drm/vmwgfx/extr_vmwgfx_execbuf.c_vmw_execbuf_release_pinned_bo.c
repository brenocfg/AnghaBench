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
struct vmw_private {int /*<<< orphan*/  cmdbuf_mutex; scalar_t__ query_cid_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  __vmw_execbuf_release_pinned_bo (struct vmw_private*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void vmw_execbuf_release_pinned_bo(struct vmw_private *dev_priv)
{
	mutex_lock(&dev_priv->cmdbuf_mutex);
	if (dev_priv->query_cid_valid)
		__vmw_execbuf_release_pinned_bo(dev_priv, NULL);
	mutex_unlock(&dev_priv->cmdbuf_mutex);
}