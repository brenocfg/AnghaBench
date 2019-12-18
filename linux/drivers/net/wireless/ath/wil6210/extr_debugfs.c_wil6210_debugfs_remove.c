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
struct TYPE_3__ {int /*<<< orphan*/  data_arr; } ;
struct wil6210_priv {int max_assoc_sta; TYPE_2__* sta; TYPE_1__ dbg_data; int /*<<< orphan*/ * debug; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_latency_bins; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_pmc_free (struct wil6210_priv*,int) ; 

void wil6210_debugfs_remove(struct wil6210_priv *wil)
{
	int i;

	debugfs_remove_recursive(wil->debug);
	wil->debug = NULL;

	kfree(wil->dbg_data.data_arr);
	for (i = 0; i < wil->max_assoc_sta; i++)
		kfree(wil->sta[i].tx_latency_bins);

	/* free pmc memory without sending command to fw, as it will
	 * be reset on the way down anyway
	 */
	wil_pmc_free(wil, false);
}