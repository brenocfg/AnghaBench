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
 int /*<<< orphan*/  AUDIO_LIPSYNC ; 
 int /*<<< orphan*/  AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_LIPSYNC ; 
 int /*<<< orphan*/  AZ_REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AZ_REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_audio_latency(
	struct audio *audio,
	int latency_in_ms)
{
	uint32_t value = 0;

	if (latency_in_ms < 0)
		latency_in_ms = 0;

	if (latency_in_ms > 255)
		latency_in_ms = 255;

	value = AZ_REG_READ(AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_LIPSYNC);

	set_reg_field_value(value, latency_in_ms,
		AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_LIPSYNC,
		AUDIO_LIPSYNC);

	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_LIPSYNC,
		value);
}