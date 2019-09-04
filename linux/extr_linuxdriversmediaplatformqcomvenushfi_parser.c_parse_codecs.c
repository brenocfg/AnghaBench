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
struct venus_core {int /*<<< orphan*/  dec_codecs; int /*<<< orphan*/  enc_codecs; } ;
struct hfi_codec_supported {int /*<<< orphan*/  enc_codecs; int /*<<< orphan*/  dec_codecs; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI_VIDEO_CODEC_HEVC ; 
 int /*<<< orphan*/  HFI_VIDEO_CODEC_SPARK ; 
 scalar_t__ IS_V1 (struct venus_core*) ; 

__attribute__((used)) static void parse_codecs(struct venus_core *core, void *data)
{
	struct hfi_codec_supported *codecs = data;

	core->dec_codecs = codecs->dec_codecs;
	core->enc_codecs = codecs->enc_codecs;

	if (IS_V1(core)) {
		core->dec_codecs &= ~HFI_VIDEO_CODEC_HEVC;
		core->dec_codecs &= ~HFI_VIDEO_CODEC_SPARK;
	}
}