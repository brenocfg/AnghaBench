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
struct dce_audio {int dummy; } ;
struct audio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AZALIA_ENDPOINT_REG_INDEX ; 
 int /*<<< orphan*/  AZALIA_F0_CODEC_ENDPOINT_DATA ; 
 int /*<<< orphan*/  AZALIA_F0_CODEC_ENDPOINT_INDEX ; 
 struct dce_audio* DCE_AUD (struct audio*) ; 
 int /*<<< orphan*/  DC_LOG_HW_AUDIO (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t read_indirect_azalia_reg(struct audio *audio, uint32_t reg_index)
{
	struct dce_audio *aud = DCE_AUD(audio);

	uint32_t value = 0;

	/* AZALIA_F0_CODEC_ENDPOINT_INDEX  endpoint index  */
	REG_SET(AZALIA_F0_CODEC_ENDPOINT_INDEX, 0,
			AZALIA_ENDPOINT_REG_INDEX, reg_index);

	/* AZALIA_F0_CODEC_ENDPOINT_DATA  endpoint data  */
	value = REG_READ(AZALIA_F0_CODEC_ENDPOINT_DATA);

	DC_LOG_HW_AUDIO("AUDIO:read_indirect_azalia_reg: index: %u  data: %u\n",
		reg_index, value);

	return value;
}