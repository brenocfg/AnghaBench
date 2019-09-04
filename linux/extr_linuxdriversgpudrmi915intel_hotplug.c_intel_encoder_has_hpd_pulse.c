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
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct TYPE_2__ {int /*<<< orphan*/ * hpd_pulse; } ;

/* Variables and functions */
 TYPE_1__* enc_to_dig_port (int /*<<< orphan*/ *) ; 
 scalar_t__ intel_encoder_is_dig_port (struct intel_encoder*) ; 

__attribute__((used)) static bool intel_encoder_has_hpd_pulse(struct intel_encoder *encoder)
{
	return intel_encoder_is_dig_port(encoder) &&
		enc_to_dig_port(&encoder->base)->hpd_pulse != NULL;
}