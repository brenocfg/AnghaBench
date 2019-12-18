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
struct cyttsp_xydata {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tt_mode; } ;
struct cyttsp {scalar_t__ state; int /*<<< orphan*/  dev; TYPE_1__ xy_data; int /*<<< orphan*/  bl_ready; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ CY_BL_STATE ; 
 scalar_t__ CY_IDLE_STATE ; 
 int /*<<< orphan*/  CY_REG_BASE ; 
 scalar_t__ GET_BOOTLOADERMODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int cyttsp_exit_bl_mode (struct cyttsp*) ; 
 int cyttsp_handshake (struct cyttsp*) ; 
 int /*<<< orphan*/  cyttsp_report_tchdata (struct cyttsp*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int ttsp_read_block_data (struct cyttsp*,int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t cyttsp_irq(int irq, void *handle)
{
	struct cyttsp *ts = handle;
	int error;

	if (unlikely(ts->state == CY_BL_STATE)) {
		complete(&ts->bl_ready);
		goto out;
	}

	/* Get touch data from CYTTSP device */
	error = ttsp_read_block_data(ts, CY_REG_BASE,
				 sizeof(struct cyttsp_xydata), &ts->xy_data);
	if (error)
		goto out;

	/* provide flow control handshake */
	error = cyttsp_handshake(ts);
	if (error)
		goto out;

	if (unlikely(ts->state == CY_IDLE_STATE))
		goto out;

	if (GET_BOOTLOADERMODE(ts->xy_data.tt_mode)) {
		/*
		 * TTSP device has reset back to bootloader mode.
		 * Restore to operational mode.
		 */
		error = cyttsp_exit_bl_mode(ts);
		if (error) {
			dev_err(ts->dev,
				"Could not return to operational mode, err: %d\n",
				error);
			ts->state = CY_IDLE_STATE;
		}
	} else {
		cyttsp_report_tchdata(ts);
	}

out:
	return IRQ_HANDLED;
}