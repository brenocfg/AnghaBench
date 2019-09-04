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
typedef  int /*<<< orphan*/  uint32_t ;
struct mdp4_crtc {int /*<<< orphan*/  vblank; int /*<<< orphan*/  pending; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_or (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* get_kms (struct drm_crtc*) ; 
 int /*<<< orphan*/  mdp_irq_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mdp4_crtc* to_mdp4_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void request_pending(struct drm_crtc *crtc, uint32_t pending)
{
	struct mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);

	atomic_or(pending, &mdp4_crtc->pending);
	mdp_irq_register(&get_kms(crtc)->base, &mdp4_crtc->vblank);
}