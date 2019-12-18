#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int capabilities; } ;
struct vmw_private {TYPE_1__ fifo; int /*<<< orphan*/ * overlay_priv; } ;

/* Variables and functions */
 int VMW_OVERLAY_CAP_MASK ; 

__attribute__((used)) static bool vmw_overlay_available(const struct vmw_private *dev_priv)
{
	return (dev_priv->overlay_priv != NULL &&
		((dev_priv->fifo.capabilities & VMW_OVERLAY_CAP_MASK) ==
		 VMW_OVERLAY_CAP_MASK));
}