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
struct c_can_priv {scalar_t__ device; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_get_sync (scalar_t__) ; 

__attribute__((used)) static inline void c_can_pm_runtime_get_sync(const struct c_can_priv *priv)
{
	if (priv->device)
		pm_runtime_get_sync(priv->device);
}