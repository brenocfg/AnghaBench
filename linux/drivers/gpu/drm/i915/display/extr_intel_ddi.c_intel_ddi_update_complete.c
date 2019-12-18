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
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct intel_crtc {int dummy; } ;
struct intel_atomic_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  enc_to_dig_port (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_tc_port_put_link (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
intel_ddi_update_complete(struct intel_atomic_state *state,
			  struct intel_encoder *encoder,
			  struct intel_crtc *crtc)
{
	intel_tc_port_put_link(enc_to_dig_port(&encoder->base));
}