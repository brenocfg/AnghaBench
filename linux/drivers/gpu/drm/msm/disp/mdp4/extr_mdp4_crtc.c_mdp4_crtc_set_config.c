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
typedef  int /*<<< orphan*/  uint32_t ;
struct mdp4_kms {int dummy; } ;
struct mdp4_crtc {int /*<<< orphan*/  dma; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_MDP4_DMA_CONFIG (int /*<<< orphan*/ ) ; 
 struct mdp4_kms* get_kms (struct drm_crtc*) ; 
 int /*<<< orphan*/  mdp4_write (struct mdp4_kms*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mdp4_crtc* to_mdp4_crtc (struct drm_crtc*) ; 

void mdp4_crtc_set_config(struct drm_crtc *crtc, uint32_t config)
{
	struct mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);
	struct mdp4_kms *mdp4_kms = get_kms(crtc);

	mdp4_write(mdp4_kms, REG_MDP4_DMA_CONFIG(mdp4_crtc->dma), config);
}