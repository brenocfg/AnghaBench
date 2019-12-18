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
struct stream_encoder {int dummy; } ;
struct audio_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dce110_se_audio_setup (struct stream_encoder*,unsigned int,struct audio_info*) ; 

void dce110_se_dp_audio_setup(
	struct stream_encoder *enc,
	unsigned int az_inst,
	struct audio_info *info)
{
	dce110_se_audio_setup(enc, az_inst, info);
}