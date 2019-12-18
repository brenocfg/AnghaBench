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
struct vmw_private {scalar_t__ has_mob; } ;

/* Variables and functions */
 int vmw_fifo_emit_dummy_gb_query (struct vmw_private*,int /*<<< orphan*/ ) ; 
 int vmw_fifo_emit_dummy_legacy_query (struct vmw_private*,int /*<<< orphan*/ ) ; 

int vmw_fifo_emit_dummy_query(struct vmw_private *dev_priv,
			      uint32_t cid)
{
	if (dev_priv->has_mob)
		return vmw_fifo_emit_dummy_gb_query(dev_priv, cid);

	return vmw_fifo_emit_dummy_legacy_query(dev_priv, cid);
}