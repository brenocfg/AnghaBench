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
struct pmic_mpp_state {int /*<<< orphan*/  dev; int /*<<< orphan*/  map; } ;
struct pmic_mpp_pad {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int regmap_write (int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 

__attribute__((used)) static int pmic_mpp_write(struct pmic_mpp_state *state,
			  struct pmic_mpp_pad *pad, unsigned int addr,
			  unsigned int val)
{
	int ret;

	ret = regmap_write(state->map, pad->base + addr, val);
	if (ret < 0)
		dev_err(state->dev, "write 0x%x failed\n", addr);

	return ret;
}