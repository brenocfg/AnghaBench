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
struct vmw_master {int dummy; } ;
struct drm_master {scalar_t__ driver_priv; } ;

/* Variables and functions */

__attribute__((used)) static inline struct vmw_master *vmw_master(struct drm_master *master)
{
	return (struct vmw_master *) master->driver_priv;
}