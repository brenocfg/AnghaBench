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
struct TYPE_2__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  reg; scalar_t__ map; } ;
struct stm32_rproc {TYPE_1__ pdds; } ;
struct rproc {int /*<<< orphan*/  dev; struct stm32_rproc* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int regmap_update_bits (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_rproc_add_coredump_trace (struct rproc*) ; 
 int stm32_rproc_set_hold_boot (struct rproc*,int) ; 

__attribute__((used)) static int stm32_rproc_start(struct rproc *rproc)
{
	struct stm32_rproc *ddata = rproc->priv;
	int err;

	stm32_rproc_add_coredump_trace(rproc);

	/* clear remote proc Deep Sleep */
	if (ddata->pdds.map) {
		err = regmap_update_bits(ddata->pdds.map, ddata->pdds.reg,
					 ddata->pdds.mask, 0);
		if (err) {
			dev_err(&rproc->dev, "failed to clear pdds\n");
			return err;
		}
	}

	err = stm32_rproc_set_hold_boot(rproc, false);
	if (err)
		return err;

	return stm32_rproc_set_hold_boot(rproc, true);
}