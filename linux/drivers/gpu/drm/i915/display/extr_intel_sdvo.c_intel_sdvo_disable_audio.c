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
struct intel_sdvo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_sdvo_set_audio_state (struct intel_sdvo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_sdvo_disable_audio(struct intel_sdvo *intel_sdvo)
{
	intel_sdvo_set_audio_state(intel_sdvo, 0);
}