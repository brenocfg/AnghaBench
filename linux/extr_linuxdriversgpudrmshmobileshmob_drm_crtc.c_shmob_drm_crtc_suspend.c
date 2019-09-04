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
struct shmob_drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  shmob_drm_crtc_stop (struct shmob_drm_crtc*) ; 

void shmob_drm_crtc_suspend(struct shmob_drm_crtc *scrtc)
{
	shmob_drm_crtc_stop(scrtc);
}