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
struct TYPE_2__ {int irq; } ;
struct drm_i915_private {TYPE_1__ lpe_audio; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 int /*<<< orphan*/  intel_irqs_enabled (struct drm_i915_private*) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler_name (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int irq_set_chip_data (int,struct drm_i915_private*) ; 
 int /*<<< orphan*/  lpe_audio_irqchip ; 

__attribute__((used)) static int lpe_audio_irq_init(struct drm_i915_private *dev_priv)
{
	int irq = dev_priv->lpe_audio.irq;

	WARN_ON(!intel_irqs_enabled(dev_priv));
	irq_set_chip_and_handler_name(irq,
				&lpe_audio_irqchip,
				handle_simple_irq,
				"hdmi_lpe_audio_irq_handler");

	return irq_set_chip_data(irq, dev_priv);
}