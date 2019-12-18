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
struct dce110_stream_encoder {int dummy; } ;

/* Variables and functions */
 struct dce110_stream_encoder* DCE110STRENC_FROM_STRENC (struct stream_encoder*) ; 
 int /*<<< orphan*/  HDMI_GC ; 
 int /*<<< orphan*/  HDMI_GC_AVMUTE ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void dce110_stream_encoder_set_avmute(
	struct stream_encoder *enc,
	bool enable)
{
	struct dce110_stream_encoder *enc110 = DCE110STRENC_FROM_STRENC(enc);
	unsigned int value = enable ? 1 : 0;

	REG_UPDATE(HDMI_GC, HDMI_GC_AVMUTE, value);
}