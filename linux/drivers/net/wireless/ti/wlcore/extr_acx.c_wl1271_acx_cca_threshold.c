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
struct TYPE_5__ {int /*<<< orphan*/  tx_energy_detection; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_cca_threshold; } ;
struct TYPE_6__ {TYPE_2__ tx; TYPE_1__ rx; } ;
struct wl1271 {TYPE_3__ conf; } ;
struct acx_energy_detection {int /*<<< orphan*/  tx_energy_detection; int /*<<< orphan*/  rx_cca_threshold; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_CCA_THRESHOLD ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct acx_energy_detection*) ; 
 struct acx_energy_detection* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct acx_energy_detection*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wl1271_acx_cca_threshold(struct wl1271 *wl)
{
	struct acx_energy_detection *detection;
	int ret;

	wl1271_debug(DEBUG_ACX, "acx cca threshold");

	detection = kzalloc(sizeof(*detection), GFP_KERNEL);
	if (!detection) {
		ret = -ENOMEM;
		goto out;
	}

	detection->rx_cca_threshold = cpu_to_le16(wl->conf.rx.rx_cca_threshold);
	detection->tx_energy_detection = wl->conf.tx.tx_energy_detection;

	ret = wl1271_cmd_configure(wl, ACX_CCA_THRESHOLD,
				   detection, sizeof(*detection));
	if (ret < 0)
		wl1271_warning("failed to set cca threshold: %d", ret);

out:
	kfree(detection);
	return ret;
}