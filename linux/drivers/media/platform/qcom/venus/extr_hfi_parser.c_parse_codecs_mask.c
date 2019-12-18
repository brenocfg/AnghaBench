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
typedef  int /*<<< orphan*/  u32 ;
struct hfi_codec_mask_supported {int /*<<< orphan*/  video_domains; int /*<<< orphan*/  codecs; } ;

/* Variables and functions */

__attribute__((used)) static void parse_codecs_mask(u32 *codecs, u32 *domain, void *data)
{
	struct hfi_codec_mask_supported *mask = data;

	*codecs = mask->codecs;
	*domain = mask->video_domains;
}