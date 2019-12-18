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
struct sti_vtg {int /*<<< orphan*/  notifier_list; struct drm_crtc* crtc; } ;
struct notifier_block {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int raw_notifier_chain_register (int /*<<< orphan*/ *,struct notifier_block*) ; 

int sti_vtg_register_client(struct sti_vtg *vtg, struct notifier_block *nb,
			    struct drm_crtc *crtc)
{
	vtg->crtc = crtc;
	return raw_notifier_chain_register(&vtg->notifier_list, nb);
}