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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev {int dummy; } ;
struct device {int dummy; } ;
struct csid_device {int /*<<< orphan*/  vdda; int /*<<< orphan*/  clock; int /*<<< orphan*/  nclocks; int /*<<< orphan*/  irq; scalar_t__ base; TYPE_1__* camss; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 scalar_t__ CAMSS_CSID_HW_VERSION ; 
 int /*<<< orphan*/  camss_disable_clocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int camss_enable_clocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct device*) ; 
 int csid_reset (struct csid_device*) ; 
 int csid_set_clock_rates (struct csid_device*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 struct csid_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int csid_set_power(struct v4l2_subdev *sd, int on)
{
	struct csid_device *csid = v4l2_get_subdevdata(sd);
	struct device *dev = csid->camss->dev;
	int ret;

	if (on) {
		u32 hw_version;

		ret = pm_runtime_get_sync(dev);
		if (ret < 0)
			return ret;

		ret = regulator_enable(csid->vdda);
		if (ret < 0) {
			pm_runtime_put_sync(dev);
			return ret;
		}

		ret = csid_set_clock_rates(csid);
		if (ret < 0) {
			regulator_disable(csid->vdda);
			pm_runtime_put_sync(dev);
			return ret;
		}

		ret = camss_enable_clocks(csid->nclocks, csid->clock, dev);
		if (ret < 0) {
			regulator_disable(csid->vdda);
			pm_runtime_put_sync(dev);
			return ret;
		}

		enable_irq(csid->irq);

		ret = csid_reset(csid);
		if (ret < 0) {
			disable_irq(csid->irq);
			camss_disable_clocks(csid->nclocks, csid->clock);
			regulator_disable(csid->vdda);
			pm_runtime_put_sync(dev);
			return ret;
		}

		hw_version = readl_relaxed(csid->base + CAMSS_CSID_HW_VERSION);
		dev_dbg(dev, "CSID HW Version = 0x%08x\n", hw_version);
	} else {
		disable_irq(csid->irq);
		camss_disable_clocks(csid->nclocks, csid->clock);
		ret = regulator_disable(csid->vdda);
		pm_runtime_put_sync(dev);
	}

	return ret;
}