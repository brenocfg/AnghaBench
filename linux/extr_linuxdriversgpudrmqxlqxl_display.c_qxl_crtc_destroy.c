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
struct qxl_crtc {int /*<<< orphan*/  cursor_bo; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_crtc_cleanup (struct drm_crtc*) ; 
 int /*<<< orphan*/  kfree (struct qxl_crtc*) ; 
 int /*<<< orphan*/  qxl_bo_unref (int /*<<< orphan*/ *) ; 
 struct qxl_crtc* to_qxl_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void qxl_crtc_destroy(struct drm_crtc *crtc)
{
	struct qxl_crtc *qxl_crtc = to_qxl_crtc(crtc);

	qxl_bo_unref(&qxl_crtc->cursor_bo);
	drm_crtc_cleanup(crtc);
	kfree(qxl_crtc);
}