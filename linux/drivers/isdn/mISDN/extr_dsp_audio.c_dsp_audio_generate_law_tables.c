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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  alaw2linear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitrev8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dsp_audio_alaw_to_s32 ; 
 int /*<<< orphan*/ * dsp_audio_alaw_to_ulaw ; 
 int /*<<< orphan*/ * dsp_audio_ulaw_to_alaw ; 
 int /*<<< orphan*/ * dsp_audio_ulaw_to_s32 ; 
 int /*<<< orphan*/  linear2alaw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linear2ulaw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ulaw2linear (int /*<<< orphan*/ ) ; 

void dsp_audio_generate_law_tables(void)
{
	int i;
	for (i = 0; i < 256; i++)
		dsp_audio_alaw_to_s32[i] = alaw2linear(bitrev8((u8)i));

	for (i = 0; i < 256; i++)
		dsp_audio_ulaw_to_s32[i] = ulaw2linear(bitrev8((u8)i));

	for (i = 0; i < 256; i++) {
		dsp_audio_alaw_to_ulaw[i] =
			linear2ulaw(dsp_audio_alaw_to_s32[i]);
		dsp_audio_ulaw_to_alaw[i] =
			linear2alaw(dsp_audio_ulaw_to_s32[i]);
	}
}