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
struct intel_digital_port {int dummy; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_encoder_cleanup (struct drm_encoder*) ; 
 struct intel_digital_port* enc_to_dig_port (struct drm_encoder*) ; 
 int /*<<< orphan*/  intel_dp_encoder_flush_work (struct drm_encoder*) ; 
 int /*<<< orphan*/  kfree (struct intel_digital_port*) ; 

__attribute__((used)) static void intel_ddi_encoder_destroy(struct drm_encoder *encoder)
{
	struct intel_digital_port *dig_port = enc_to_dig_port(encoder);

	intel_dp_encoder_flush_work(encoder);

	drm_encoder_cleanup(encoder);
	kfree(dig_port);
}