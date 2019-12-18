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
struct ltq_pinmux_info {int /*<<< orphan*/  dev; int /*<<< orphan*/ * mfp; } ;
struct ltq_pin_group {int npins; int /*<<< orphan*/ * pins; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int match_mfp (struct ltq_pinmux_info const*,int /*<<< orphan*/ ) ; 
 int match_mux (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int match_group_mux(const struct ltq_pin_group *grp,
			   const struct ltq_pinmux_info *info,
			   unsigned mux)
{
	int i, pin, ret = 0;
	for (i = 0; i < grp->npins; i++) {
		pin = match_mfp(info, grp->pins[i]);
		if (pin < 0) {
			dev_err(info->dev, "could not find mfp for pin %d\n",
				grp->pins[i]);
			return -EINVAL;
		}
		ret = match_mux(&info->mfp[pin], mux);
		if (ret < 0) {
			dev_err(info->dev, "Can't find mux %d on pin%d\n",
				mux, pin);
			break;
		}
	}
	return ret;
}