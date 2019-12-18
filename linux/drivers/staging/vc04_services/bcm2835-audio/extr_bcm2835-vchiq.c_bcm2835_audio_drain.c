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
struct TYPE_2__ {int draining; } ;
struct vc_audio_msg {TYPE_1__ stop; int /*<<< orphan*/  type; } ;
struct bcm2835_alsa_stream {int /*<<< orphan*/  instance; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC_AUDIO_MSG_TYPE_STOP ; 
 int bcm2835_audio_send_msg (int /*<<< orphan*/ ,struct vc_audio_msg*,int) ; 

int bcm2835_audio_drain(struct bcm2835_alsa_stream *alsa_stream)
{
	struct vc_audio_msg m = {
		.type = VC_AUDIO_MSG_TYPE_STOP,
		.stop.draining = 1,
	};

	return bcm2835_audio_send_msg(alsa_stream->instance, &m, false);
}