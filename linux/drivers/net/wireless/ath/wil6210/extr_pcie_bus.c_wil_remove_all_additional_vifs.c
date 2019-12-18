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
struct wil6210_vif {int /*<<< orphan*/  mid; } ;
struct wil6210_priv {struct wil6210_vif** vifs; } ;

/* Variables and functions */
 int GET_MAX_VIFS (struct wil6210_priv*) ; 
 int /*<<< orphan*/  wil_vif_prepare_stop (struct wil6210_vif*) ; 
 int /*<<< orphan*/  wil_vif_remove (struct wil6210_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wil_remove_all_additional_vifs(struct wil6210_priv *wil)
{
	struct wil6210_vif *vif;
	int i;

	for (i = 1; i < GET_MAX_VIFS(wil); i++) {
		vif = wil->vifs[i];
		if (vif) {
			wil_vif_prepare_stop(vif);
			wil_vif_remove(wil, vif->mid);
		}
	}
}