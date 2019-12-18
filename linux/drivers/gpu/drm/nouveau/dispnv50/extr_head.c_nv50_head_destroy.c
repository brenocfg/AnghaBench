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
struct nv50_head {int /*<<< orphan*/  olut; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_crtc_cleanup (struct drm_crtc*) ; 
 int /*<<< orphan*/  kfree (struct nv50_head*) ; 
 struct nv50_head* nv50_head (struct drm_crtc*) ; 
 int /*<<< orphan*/  nv50_lut_fini (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nv50_head_destroy(struct drm_crtc *crtc)
{
	struct nv50_head *head = nv50_head(crtc);
	nv50_lut_fini(&head->olut);
	drm_crtc_cleanup(crtc);
	kfree(head);
}