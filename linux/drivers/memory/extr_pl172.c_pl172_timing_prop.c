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
struct pl172_data {int rate; int base; } ;
struct device_node {int dummy; } ;
struct amba_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  NSEC_PER_MSEC ; 
 struct pl172_data* amba_get_drvdata (struct amba_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node const*,char const*,int*) ; 
 scalar_t__ readl (int) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static int pl172_timing_prop(struct amba_device *adev,
			     const struct device_node *np, const char *name,
			     u32 reg_offset, u32 max, int start)
{
	struct pl172_data *pl172 = amba_get_drvdata(adev);
	int cycles;
	u32 val;

	if (!of_property_read_u32(np, name, &val)) {
		cycles = DIV_ROUND_UP(val * pl172->rate, NSEC_PER_MSEC) - start;
		if (cycles < 0) {
			cycles = 0;
		} else if (cycles > max) {
			dev_err(&adev->dev, "%s timing too tight\n", name);
			return -EINVAL;
		}

		writel(cycles, pl172->base + reg_offset);
	}

	dev_dbg(&adev->dev, "%s: %u cycle(s)\n", name, start +
				readl(pl172->base + reg_offset));

	return 0;
}