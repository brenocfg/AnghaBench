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
typedef  int u8 ;
typedef  int u32 ;
struct intel_uncore {int dummy; } ;
struct TYPE_2__ {int fmax; int fstart; int max_delay; int min_delay; int cur_delay; int last_count1; int last_count2; int /*<<< orphan*/  last_time2; int /*<<< orphan*/  last_time1; } ;
struct drm_i915_private {TYPE_1__ ips; struct intel_uncore uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIEC ; 
 int /*<<< orphan*/  DDREC ; 
 int /*<<< orphan*/  DMIEC ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int,int,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  GFXEC ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int MCPPCE_EN ; 
 int MEMCTL_CMD_STS ; 
 int /*<<< orphan*/  MEMIHYST ; 
 int /*<<< orphan*/  MEMINTREN ; 
 int MEMINT_CX_SUPR_EN ; 
 int MEMINT_EVAL_CHG_EN ; 
 int /*<<< orphan*/  MEMMODECTL ; 
 int MEMMODE_FMAX_MASK ; 
 int MEMMODE_FMAX_SHIFT ; 
 int MEMMODE_FMIN_MASK ; 
 int MEMMODE_FSTART_MASK ; 
 int MEMMODE_FSTART_SHIFT ; 
 int MEMMODE_SWMODE_EN ; 
 int /*<<< orphan*/  MEMSWCTL ; 
 int /*<<< orphan*/  PMMISC ; 
 int /*<<< orphan*/  PXVFREQ (int) ; 
 int PXVFREQ_PX_MASK ; 
 int PXVFREQ_PX_SHIFT ; 
 int /*<<< orphan*/  RCBMAXAVG ; 
 int /*<<< orphan*/  RCBMINAVG ; 
 int /*<<< orphan*/  RCDNEI ; 
 int /*<<< orphan*/  RCUPEI ; 
 int /*<<< orphan*/  TSC1 ; 
 int TSE ; 
 int /*<<< orphan*/  VIDSTART ; 
 int /*<<< orphan*/  intel_uncore_posting_read (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int intel_uncore_read (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_write (struct intel_uncore*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_uncore_write16 (struct intel_uncore*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ironlake_set_drps (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_raw_ns () ; 
 int /*<<< orphan*/  mchdev_lock ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ wait_for_atomic (int,int) ; 

__attribute__((used)) static void ironlake_enable_drps(struct drm_i915_private *dev_priv)
{
	struct intel_uncore *uncore = &dev_priv->uncore;
	u32 rgvmodectl;
	u8 fmax, fmin, fstart, vstart;

	spin_lock_irq(&mchdev_lock);

	rgvmodectl = intel_uncore_read(uncore, MEMMODECTL);

	/* Enable temp reporting */
	intel_uncore_write16(uncore, PMMISC, I915_READ(PMMISC) | MCPPCE_EN);
	intel_uncore_write16(uncore, TSC1, I915_READ(TSC1) | TSE);

	/* 100ms RC evaluation intervals */
	intel_uncore_write(uncore, RCUPEI, 100000);
	intel_uncore_write(uncore, RCDNEI, 100000);

	/* Set max/min thresholds to 90ms and 80ms respectively */
	intel_uncore_write(uncore, RCBMAXAVG, 90000);
	intel_uncore_write(uncore, RCBMINAVG, 80000);

	intel_uncore_write(uncore, MEMIHYST, 1);

	/* Set up min, max, and cur for interrupt handling */
	fmax = (rgvmodectl & MEMMODE_FMAX_MASK) >> MEMMODE_FMAX_SHIFT;
	fmin = (rgvmodectl & MEMMODE_FMIN_MASK);
	fstart = (rgvmodectl & MEMMODE_FSTART_MASK) >>
		MEMMODE_FSTART_SHIFT;

	vstart = (intel_uncore_read(uncore, PXVFREQ(fstart)) &
		  PXVFREQ_PX_MASK) >> PXVFREQ_PX_SHIFT;

	dev_priv->ips.fmax = fmax; /* IPS callback will increase this */
	dev_priv->ips.fstart = fstart;

	dev_priv->ips.max_delay = fstart;
	dev_priv->ips.min_delay = fmin;
	dev_priv->ips.cur_delay = fstart;

	DRM_DEBUG_DRIVER("fmax: %d, fmin: %d, fstart: %d\n",
			 fmax, fmin, fstart);

	intel_uncore_write(uncore,
			   MEMINTREN,
			   MEMINT_CX_SUPR_EN | MEMINT_EVAL_CHG_EN);

	/*
	 * Interrupts will be enabled in ironlake_irq_postinstall
	 */

	intel_uncore_write(uncore, VIDSTART, vstart);
	intel_uncore_posting_read(uncore, VIDSTART);

	rgvmodectl |= MEMMODE_SWMODE_EN;
	intel_uncore_write(uncore, MEMMODECTL, rgvmodectl);

	if (wait_for_atomic((intel_uncore_read(uncore, MEMSWCTL) &
			     MEMCTL_CMD_STS) == 0, 10))
		DRM_ERROR("stuck trying to change perf mode\n");
	mdelay(1);

	ironlake_set_drps(dev_priv, fstart);

	dev_priv->ips.last_count1 =
		intel_uncore_read(uncore, DMIEC) +
		intel_uncore_read(uncore, DDREC) +
		intel_uncore_read(uncore, CSIEC);
	dev_priv->ips.last_time1 = jiffies_to_msecs(jiffies);
	dev_priv->ips.last_count2 = intel_uncore_read(uncore, GFXEC);
	dev_priv->ips.last_time2 = ktime_get_raw_ns();

	spin_unlock_irq(&mchdev_lock);
}