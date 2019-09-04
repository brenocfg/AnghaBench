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
struct intel_dp_mst_encoder {int dummy; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_encoder_cleanup (struct drm_encoder*) ; 
 struct intel_dp_mst_encoder* enc_to_mst (struct drm_encoder*) ; 
 int /*<<< orphan*/  kfree (struct intel_dp_mst_encoder*) ; 

__attribute__((used)) static void intel_dp_mst_encoder_destroy(struct drm_encoder *encoder)
{
	struct intel_dp_mst_encoder *intel_mst = enc_to_mst(encoder);

	drm_encoder_cleanup(encoder);
	kfree(intel_mst);
}