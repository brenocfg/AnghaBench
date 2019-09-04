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
struct TYPE_2__ {scalar_t__ RRC_FRC; scalar_t__ RC_RLC_FLC; scalar_t__ RL_RC; scalar_t__ RR; int /*<<< orphan*/  FC; int /*<<< orphan*/  LFE; int /*<<< orphan*/  FR; int /*<<< orphan*/  FL; } ;
union audio_cea_channels {TYPE_1__ channels; int /*<<< orphan*/  member_0; } ;
struct audio_speaker_flags {scalar_t__ RLC_RRC; scalar_t__ FLC_FRC; scalar_t__ RC; scalar_t__ RL_RR; int /*<<< orphan*/  FC; int /*<<< orphan*/  LFE; int /*<<< orphan*/  FL_FR; } ;

/* Variables and functions */

__attribute__((used)) static union audio_cea_channels speakers_to_channels(
	struct audio_speaker_flags speaker_flags)
{
	union audio_cea_channels cea_channels = {0};

	/* these are one to one */
	cea_channels.channels.FL = speaker_flags.FL_FR;
	cea_channels.channels.FR = speaker_flags.FL_FR;
	cea_channels.channels.LFE = speaker_flags.LFE;
	cea_channels.channels.FC = speaker_flags.FC;

	/* if Rear Left and Right exist move RC speaker to channel 7
	 * otherwise to channel 5
	 */
	if (speaker_flags.RL_RR) {
		cea_channels.channels.RL_RC = speaker_flags.RL_RR;
		cea_channels.channels.RR = speaker_flags.RL_RR;
		cea_channels.channels.RC_RLC_FLC = speaker_flags.RC;
	} else {
		cea_channels.channels.RL_RC = speaker_flags.RC;
	}

	/* FRONT Left Right Center and REAR Left Right Center are exclusive */
	if (speaker_flags.FLC_FRC) {
		cea_channels.channels.RC_RLC_FLC = speaker_flags.FLC_FRC;
		cea_channels.channels.RRC_FRC = speaker_flags.FLC_FRC;
	} else {
		cea_channels.channels.RC_RLC_FLC = speaker_flags.RLC_RRC;
		cea_channels.channels.RRC_FRC = speaker_flags.RLC_RRC;
	}

	return cea_channels;
}