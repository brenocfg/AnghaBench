#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  reg; scalar_t__ map; } ;
struct stm32_rproc {TYPE_2__ pdds; int /*<<< orphan*/  rst; TYPE_1__* mb; } ;
struct rproc {scalar_t__ state; int /*<<< orphan*/  dev; struct stm32_rproc* priv; } ;
struct TYPE_3__ {scalar_t__ chan; } ;

/* Variables and functions */
 scalar_t__ RPROC_OFFLINE ; 
 int /*<<< orphan*/  STM32_MBX_SHUTDOWN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int mbox_send_message (scalar_t__,int*) ; 
 int regmap_update_bits (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int reset_control_assert (int /*<<< orphan*/ ) ; 
 int stm32_rproc_mbox_idx (struct rproc*,int /*<<< orphan*/ ) ; 
 int stm32_rproc_set_hold_boot (struct rproc*,int) ; 

__attribute__((used)) static int stm32_rproc_stop(struct rproc *rproc)
{
	struct stm32_rproc *ddata = rproc->priv;
	int err, dummy_data, idx;

	/* request shutdown of the remote processor */
	if (rproc->state != RPROC_OFFLINE) {
		idx = stm32_rproc_mbox_idx(rproc, STM32_MBX_SHUTDOWN);
		if (idx >= 0 && ddata->mb[idx].chan) {
			/* a dummy data is sent to allow to block on transmit */
			err = mbox_send_message(ddata->mb[idx].chan,
						&dummy_data);
			if (err < 0)
				dev_warn(&rproc->dev, "warning: remote FW shutdown without ack\n");
		}
	}

	err = stm32_rproc_set_hold_boot(rproc, true);
	if (err)
		return err;

	err = reset_control_assert(ddata->rst);
	if (err) {
		dev_err(&rproc->dev, "failed to assert the reset\n");
		return err;
	}

	/* to allow platform Standby power mode, set remote proc Deep Sleep */
	if (ddata->pdds.map) {
		err = regmap_update_bits(ddata->pdds.map, ddata->pdds.reg,
					 ddata->pdds.mask, 1);
		if (err) {
			dev_err(&rproc->dev, "failed to set pdds\n");
			return err;
		}
	}

	return 0;
}