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
typedef  int uint32_t ;
struct audio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_CONFIGURATION_DEFAULT ; 
 int AZ_REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORT_CONNECTIVITY ; 
 int get_reg_field_value (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool dce_aud_endpoint_valid(struct audio *audio)
{
	uint32_t value;
	uint32_t port_connectivity;

	value = AZ_REG_READ(
			AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_CONFIGURATION_DEFAULT);

	port_connectivity = get_reg_field_value(value,
			AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_CONFIGURATION_DEFAULT,
			PORT_CONNECTIVITY);

	return !(port_connectivity == 1);
}