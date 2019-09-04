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
struct qib_devdata {TYPE_2__* cspec; int /*<<< orphan*/  pport; TYPE_1__* pcidev; } ;
struct firmware {int dummy; } ;
struct TYPE_4__ {int serdes_first_init_done; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SD7220_FW_NAME ; 
 int /*<<< orphan*/  START_EQ1 (int /*<<< orphan*/ ) ; 
 int ibsd_mod_allchnls (struct qib_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kr_ibserdesctrl ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*) ; 
 int /*<<< orphan*/  qib_ibsd_reset (struct qib_devdata*,int) ; 
 int qib_ibsd_ucode_loaded (int /*<<< orphan*/ ,struct firmware const*) ; 
 int qib_internal_presets (struct qib_devdata*) ; 
 int qib_read_kreg64 (struct qib_devdata*,int /*<<< orphan*/ ) ; 
 int qib_sd7220_ib_load (struct qib_devdata*,struct firmware const*) ; 
 int qib_sd7220_ib_vfy (struct qib_devdata*,struct firmware const*) ; 
 int qib_sd_dactrim (struct qib_devdata*) ; 
 int qib_sd_early (struct qib_devdata*) ; 
 scalar_t__ qib_sd_setvals (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_sd_trimdone_monitor (struct qib_devdata*,char*) ; 
 int qib_sd_trimdone_poll (struct qib_devdata*) ; 
 int qib_sd_trimself (struct qib_devdata*,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_7220_relock_poll (struct qib_devdata*,int) ; 

int qib_sd7220_init(struct qib_devdata *dd)
{
	const struct firmware *fw;
	int ret = 1; /* default to failure */
	int first_reset, was_reset;

	/* SERDES MPU reset recorded in D0 */
	was_reset = (qib_read_kreg64(dd, kr_ibserdesctrl) & 1);
	if (!was_reset) {
		/* entered with reset not asserted, we need to do it */
		qib_ibsd_reset(dd, 1);
		qib_sd_trimdone_monitor(dd, "Driver-reload");
	}

	ret = request_firmware(&fw, SD7220_FW_NAME, &dd->pcidev->dev);
	if (ret) {
		qib_dev_err(dd, "Failed to load IB SERDES image\n");
		goto done;
	}

	/* Substitute our deduced value for was_reset */
	ret = qib_ibsd_ucode_loaded(dd->pport, fw);
	if (ret < 0)
		goto bail;

	first_reset = !ret; /* First reset if IBSD uCode not yet loaded */
	/*
	 * Alter some regs per vendor latest doc, reset-defaults
	 * are not right for IB.
	 */
	ret = qib_sd_early(dd);
	if (ret < 0) {
		qib_dev_err(dd, "Failed to set IB SERDES early defaults\n");
		goto bail;
	}
	/*
	 * Set DAC manual trim IB.
	 * We only do this once after chip has been reset (usually
	 * same as once per system boot).
	 */
	if (first_reset) {
		ret = qib_sd_dactrim(dd);
		if (ret < 0) {
			qib_dev_err(dd, "Failed IB SERDES DAC trim\n");
			goto bail;
		}
	}
	/*
	 * Set various registers (DDS and RXEQ) that will be
	 * controlled by IBC (in 1.2 mode) to reasonable preset values
	 * Calling the "internal" version avoids the "check for needed"
	 * and "trimdone monitor" that might be counter-productive.
	 */
	ret = qib_internal_presets(dd);
	if (ret < 0) {
		qib_dev_err(dd, "Failed to set IB SERDES presets\n");
		goto bail;
	}
	ret = qib_sd_trimself(dd, 0x80);
	if (ret < 0) {
		qib_dev_err(dd, "Failed to set IB SERDES TRIMSELF\n");
		goto bail;
	}

	/* Load image, then try to verify */
	ret = 0;        /* Assume success */
	if (first_reset) {
		int vfy;
		int trim_done;

		ret = qib_sd7220_ib_load(dd, fw);
		if (ret < 0) {
			qib_dev_err(dd, "Failed to load IB SERDES image\n");
			goto bail;
		} else {
			/* Loaded image, try to verify */
			vfy = qib_sd7220_ib_vfy(dd, fw);
			if (vfy != ret) {
				qib_dev_err(dd, "SERDES PRAM VFY failed\n");
				goto bail;
			} /* end if verified */
		} /* end if loaded */

		/*
		 * Loaded and verified. Almost good...
		 * hold "success" in ret
		 */
		ret = 0;
		/*
		 * Prev steps all worked, continue bringup
		 * De-assert RESET to uC, only in first reset, to allow
		 * trimming.
		 *
		 * Since our default setup sets START_EQ1 to
		 * PRESET, we need to clear that for this very first run.
		 */
		ret = ibsd_mod_allchnls(dd, START_EQ1(0), 0, 0x38);
		if (ret < 0) {
			qib_dev_err(dd, "Failed clearing START_EQ1\n");
			goto bail;
		}

		qib_ibsd_reset(dd, 0);
		/*
		 * If this is not the first reset, trimdone should be set
		 * already. We may need to check about this.
		 */
		trim_done = qib_sd_trimdone_poll(dd);
		/*
		 * Whether or not trimdone succeeded, we need to put the
		 * uC back into reset to avoid a possible fight with the
		 * IBC state-machine.
		 */
		qib_ibsd_reset(dd, 1);

		if (!trim_done) {
			qib_dev_err(dd, "No TRIMDONE seen\n");
			goto bail;
		}
		/*
		 * DEBUG: check each time we reset if trimdone bits have
		 * gotten cleared, and re-set them.
		 */
		qib_sd_trimdone_monitor(dd, "First-reset");
		/* Remember so we do not re-do the load, dactrim, etc. */
		dd->cspec->serdes_first_init_done = 1;
	}
	/*
	 * setup for channel training and load values for
	 * RxEq and DDS in tables used by IBC in IB1.2 mode
	 */
	ret = 0;
	if (qib_sd_setvals(dd) >= 0)
		goto done;
bail:
	ret = 1;
done:
	/* start relock timer regardless, but start at 1 second */
	set_7220_relock_poll(dd, -1);

	release_firmware(fw);
	return ret;
}