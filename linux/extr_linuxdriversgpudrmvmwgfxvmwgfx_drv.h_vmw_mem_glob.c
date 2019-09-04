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
struct TYPE_2__ {scalar_t__ object; } ;
struct vmw_private {TYPE_1__ mem_global_ref; } ;
struct ttm_mem_global {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ttm_mem_global *vmw_mem_glob(struct vmw_private *dev_priv)
{
	return (struct ttm_mem_global *) dev_priv->mem_global_ref.object;
}