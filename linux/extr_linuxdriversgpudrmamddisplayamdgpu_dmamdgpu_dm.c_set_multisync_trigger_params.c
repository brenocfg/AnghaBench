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
struct TYPE_2__ {int /*<<< orphan*/  delay; int /*<<< orphan*/  event; scalar_t__ enabled; } ;
struct dc_stream_state {TYPE_1__ triggered_crtc_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC_EVENT_VSYNC_RISING ; 
 int /*<<< orphan*/  TRIGGER_DELAY_NEXT_LINE ; 

__attribute__((used)) static void set_multisync_trigger_params(
		struct dc_stream_state *stream)
{
	if (stream->triggered_crtc_reset.enabled) {
		stream->triggered_crtc_reset.event = CRTC_EVENT_VSYNC_RISING;
		stream->triggered_crtc_reset.delay = TRIGGER_DELAY_NEXT_LINE;
	}
}