#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int enabled; int endless; } ;
struct ath_spec_scan_priv {int spectral_mode; TYPE_1__ spec_config; struct ath_hw* ah; } ;
struct ath_hw {int dummy; } ;
struct ath_common {int dummy; } ;
typedef  enum spectral_mode { ____Placeholder_spectral_mode } spectral_mode ;
struct TYPE_6__ {int /*<<< orphan*/  (* spectral_scan_config ) (struct ath_hw*,TYPE_1__*) ;int /*<<< orphan*/  spectral_scan_trigger; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* restore ) (struct ath_common*) ;int /*<<< orphan*/  (* wakeup ) (struct ath_common*) ;} ;

/* Variables and functions */
#define  SPECTRAL_BACKGROUND 131 
#define  SPECTRAL_CHANSCAN 130 
#define  SPECTRAL_DISABLED 129 
#define  SPECTRAL_MANUAL 128 
 TYPE_3__* ath9k_hw_ops (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*) ; 
 TYPE_2__* ath_ps_ops (struct ath_common*) ; 
 int /*<<< orphan*/  stub1 (struct ath_common*) ; 
 int /*<<< orphan*/  stub2 (struct ath_hw*,TYPE_1__*) ; 
 int /*<<< orphan*/  stub3 (struct ath_common*) ; 

int ath9k_cmn_spectral_scan_config(struct ath_common *common,
			       struct ath_spec_scan_priv *spec_priv,
			       enum spectral_mode spectral_mode)
{
	struct ath_hw *ah = spec_priv->ah;

	if (!ath9k_hw_ops(ah)->spectral_scan_trigger) {
		ath_err(common, "spectrum analyzer not implemented on this hardware\n");
		return -1;
	}

	switch (spectral_mode) {
	case SPECTRAL_DISABLED:
		spec_priv->spec_config.enabled = 0;
		break;
	case SPECTRAL_BACKGROUND:
		/* send endless samples.
		 * TODO: is this really useful for "background"?
		 */
		spec_priv->spec_config.endless = 1;
		spec_priv->spec_config.enabled = 1;
		break;
	case SPECTRAL_CHANSCAN:
	case SPECTRAL_MANUAL:
		spec_priv->spec_config.endless = 0;
		spec_priv->spec_config.enabled = 1;
		break;
	default:
		return -1;
	}

	ath_ps_ops(common)->wakeup(common);
	ath9k_hw_ops(ah)->spectral_scan_config(ah, &spec_priv->spec_config);
	ath_ps_ops(common)->restore(common);

	spec_priv->spectral_mode = spectral_mode;

	return 0;
}