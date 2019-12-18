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
typedef  int u32 ;
struct intel_th_output {int dummy; } ;
struct intel_th_device {int /*<<< orphan*/  dev; } ;
struct gth_device {scalar_t__ base; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  CTS_CTL_SEQUENCER_ENABLE ; 
 unsigned long CTS_TRIG_WAITLOOP_DEPTH ; 
 scalar_t__ REG_CTS_CTL ; 
 scalar_t__ REG_CTS_STAT ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct gth_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_th_gth_start (struct gth_device*,struct intel_th_output*) ; 
 int /*<<< orphan*/  intel_th_gth_stop (struct gth_device*,struct intel_th_output*,int) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void intel_th_gth_switch(struct intel_th_device *thdev,
				struct intel_th_output *output)
{
	struct gth_device *gth = dev_get_drvdata(&thdev->dev);
	unsigned long count;
	u32 reg;

	/* trigger */
	iowrite32(0, gth->base + REG_CTS_CTL);
	iowrite32(CTS_CTL_SEQUENCER_ENABLE, gth->base + REG_CTS_CTL);
	/* wait on trigger status */
	for (reg = 0, count = CTS_TRIG_WAITLOOP_DEPTH;
	     count && !(reg & BIT(4)); count--) {
		reg = ioread32(gth->base + REG_CTS_STAT);
		cpu_relax();
	}
	if (!count)
		dev_dbg(&thdev->dev, "timeout waiting for CTS Trigger\n");

	/* De-assert the trigger */
	iowrite32(0, gth->base + REG_CTS_CTL);

	intel_th_gth_stop(gth, output, false);
	intel_th_gth_start(gth, output);
}