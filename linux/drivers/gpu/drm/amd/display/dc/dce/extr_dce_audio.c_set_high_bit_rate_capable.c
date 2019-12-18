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
struct audio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_HBR ; 
 int /*<<< orphan*/  AZ_REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AZ_REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HBR_CAPABLE ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_high_bit_rate_capable(
	struct audio *audio,
	bool capable)
{
	uint32_t value = 0;

	/* set high bit rate audio capable*/
	value = AZ_REG_READ(AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_HBR);

	set_reg_field_value(value, capable,
		AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_HBR,
		HBR_CAPABLE);

	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_HBR, value);
}