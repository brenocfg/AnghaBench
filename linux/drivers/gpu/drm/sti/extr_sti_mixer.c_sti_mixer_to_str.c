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
struct sti_mixer {int id; } ;

/* Variables and functions */
#define  STI_MIXER_AUX 129 
#define  STI_MIXER_MAIN 128 

const char *sti_mixer_to_str(struct sti_mixer *mixer)
{
	switch (mixer->id) {
	case STI_MIXER_MAIN:
		return "MAIN_MIXER";
	case STI_MIXER_AUX:
		return "AUX_MIXER";
	default:
		return "<UNKNOWN MIXER>";
	}
}