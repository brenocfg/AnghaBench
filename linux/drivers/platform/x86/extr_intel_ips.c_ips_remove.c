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
typedef  int u64 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ips_driver {int orig_turbo_limit; scalar_t__ monitor; scalar_t__ adjust; int /*<<< orphan*/  irq; scalar_t__ gpu_turbo_disable; scalar_t__ gpu_busy; scalar_t__ gpu_lower; scalar_t__ gpu_raise; scalar_t__ read_mch_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  TURBO_POWER_CURRENT_LIMIT ; 
 int TURBO_TDC_OVR_EN ; 
 int TURBO_TDP_OVR_EN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ips_driver*) ; 
 int /*<<< orphan*/  i915_gpu_busy ; 
 int /*<<< orphan*/  i915_gpu_lower ; 
 int /*<<< orphan*/  i915_gpu_raise ; 
 int /*<<< orphan*/  i915_gpu_turbo_disable ; 
 int /*<<< orphan*/  i915_read_mch_val ; 
 int /*<<< orphan*/  ips_debugfs_cleanup (struct ips_driver*) ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 struct ips_driver* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  symbol_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ips_remove(struct pci_dev *dev)
{
	struct ips_driver *ips = pci_get_drvdata(dev);
	u64 turbo_override;

	ips_debugfs_cleanup(ips);

	/* Release i915 driver */
	if (ips->read_mch_val)
		symbol_put(i915_read_mch_val);
	if (ips->gpu_raise)
		symbol_put(i915_gpu_raise);
	if (ips->gpu_lower)
		symbol_put(i915_gpu_lower);
	if (ips->gpu_busy)
		symbol_put(i915_gpu_busy);
	if (ips->gpu_turbo_disable)
		symbol_put(i915_gpu_turbo_disable);

	rdmsrl(TURBO_POWER_CURRENT_LIMIT, turbo_override);
	turbo_override &= ~(TURBO_TDC_OVR_EN | TURBO_TDP_OVR_EN);
	wrmsrl(TURBO_POWER_CURRENT_LIMIT, turbo_override);
	wrmsrl(TURBO_POWER_CURRENT_LIMIT, ips->orig_turbo_limit);

	free_irq(ips->irq, ips);
	pci_free_irq_vectors(dev);
	if (ips->adjust)
		kthread_stop(ips->adjust);
	if (ips->monitor)
		kthread_stop(ips->monitor);
	dev_dbg(&dev->dev, "IPS driver removed\n");
}