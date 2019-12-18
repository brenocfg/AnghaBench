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
 int /*<<< orphan*/  AZALIA_ENDPOINT_REG_DATA ; 
 int /*<<< orphan*/  AZALIA_ENDPOINT_REG_INDEX ; 
 int /*<<< orphan*/  AZALIA_F0_CODEC_ENDPOINT_DATA ; 
 int /*<<< orphan*/  AZALIA_F0_CODEC_ENDPOINT_INDEX ; 
 struct dce_audio* DCE_AUD (struct audio*) ; 
 int /*<<< orphan*/  DC_LOG_HW_AUDIO (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_indirect_azalia_reg(struct audio *audio,
	uint32_t reg_index,
	uint32_t reg_data)
{
	struct dce_audio *aud = DCE_AUD(audio);

	/* AZALIA_F0_CODEC_ENDPOINT_INDEX  endpoint index  */
	REG_SET(AZALIA_F0_CODEC_ENDPOINT_INDEX, 0,
			AZALIA_ENDPOINT_REG_INDEX, reg_index);

	/* AZALIA_F0_CODEC_ENDPOINT_DATA  endpoint data  */
	REG_SET(AZALIA_F0_CODEC_ENDPOINT_DATA, 0,
			AZALIA_ENDPOINT_REG_DATA, reg_data);

	DC_LOG_HW_AUDIO("AUDIO:write_indirect_azalia_reg: index: %u  data: %u\n",
		reg_index, reg_data);
}