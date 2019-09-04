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
struct mdp4_dtv_encoder {int dummy; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bs_fini (struct mdp4_dtv_encoder*) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (struct drm_encoder*) ; 
 int /*<<< orphan*/  kfree (struct mdp4_dtv_encoder*) ; 
 struct mdp4_dtv_encoder* to_mdp4_dtv_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void mdp4_dtv_encoder_destroy(struct drm_encoder *encoder)
{
	struct mdp4_dtv_encoder *mdp4_dtv_encoder = to_mdp4_dtv_encoder(encoder);
	bs_fini(mdp4_dtv_encoder);
	drm_encoder_cleanup(encoder);
	kfree(mdp4_dtv_encoder);
}