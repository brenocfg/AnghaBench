#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct audio_info {size_t mode_count; TYPE_1__* modes; } ;
typedef  enum audio_format_code { ____Placeholder_audio_format_code } audio_format_code ;
struct TYPE_2__ {int format_code; scalar_t__ channel_count; } ;

/* Variables and functions */

__attribute__((used)) static bool is_audio_format_supported(
	const struct audio_info *audio_info,
	enum audio_format_code audio_format_code,
	uint32_t *format_index)
{
	uint32_t index;
	uint32_t max_channe_index = 0;
	bool found = false;

	if (audio_info == NULL)
		return found;

	/* pass through whole array */
	for (index = 0; index < audio_info->mode_count; index++) {
		if (audio_info->modes[index].format_code == audio_format_code) {
			if (found) {
				/* format has multiply entries, choose one with
				 *  highst number of channels */
				if (audio_info->modes[index].channel_count >
		audio_info->modes[max_channe_index].channel_count) {
					max_channe_index = index;
				}
			} else {
				/* format found, save it's index */
				found = true;
				max_channe_index = index;
			}
		}
	}

	/* return index */
	if (found && format_index != NULL)
		*format_index = max_channe_index;

	return found;
}