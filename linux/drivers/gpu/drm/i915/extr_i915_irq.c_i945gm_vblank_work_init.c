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
struct TYPE_2__ {int /*<<< orphan*/  pm_qos; int /*<<< orphan*/  c3_disable_latency; int /*<<< orphan*/  work; } ;
struct drm_i915_private {TYPE_1__ i945gm_vblank; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM_QOS_CPU_DMA_LATENCY ; 
 int /*<<< orphan*/  PM_QOS_DEFAULT_VALUE ; 
 int /*<<< orphan*/  cstate_disable_latency (char*) ; 
 int /*<<< orphan*/  i945gm_vblank_work_func ; 
 int /*<<< orphan*/  pm_qos_add_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i945gm_vblank_work_init(struct drm_i915_private *dev_priv)
{
	INIT_WORK(&dev_priv->i945gm_vblank.work,
		  i945gm_vblank_work_func);

	dev_priv->i945gm_vblank.c3_disable_latency =
		cstate_disable_latency("C3");
	pm_qos_add_request(&dev_priv->i945gm_vblank.pm_qos,
			   PM_QOS_CPU_DMA_LATENCY,
			   PM_QOS_DEFAULT_VALUE);
}