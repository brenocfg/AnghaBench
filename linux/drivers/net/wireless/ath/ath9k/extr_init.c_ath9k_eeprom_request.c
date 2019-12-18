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
struct ath_softc {int /*<<< orphan*/  dev; struct ath_hw* sc_ah; } ;
struct ath_hw {int /*<<< orphan*/  eeprom_blob; } ;
struct ath9k_eeprom_ctx {int /*<<< orphan*/  complete; struct ath_hw* ah; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  ath9k_eeprom_request_cb ; 
 int /*<<< orphan*/  ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ath9k_eeprom_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath9k_eeprom_request(struct ath_softc *sc, const char *name)
{
	struct ath9k_eeprom_ctx ec;
	struct ath_hw *ah = sc->sc_ah;
	int err;

	/* try to load the EEPROM content asynchronously */
	init_completion(&ec.complete);
	ec.ah = sc->sc_ah;

	err = request_firmware_nowait(THIS_MODULE, 1, name, sc->dev, GFP_KERNEL,
				      &ec, ath9k_eeprom_request_cb);
	if (err < 0) {
		ath_err(ath9k_hw_common(ah),
			"EEPROM request failed\n");
		return err;
	}

	wait_for_completion(&ec.complete);

	if (!ah->eeprom_blob) {
		ath_err(ath9k_hw_common(ah),
			"Unable to load EEPROM file %s\n", name);
		return -EINVAL;
	}

	return 0;
}