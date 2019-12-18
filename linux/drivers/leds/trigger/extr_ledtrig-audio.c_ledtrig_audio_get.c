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
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;
typedef  enum led_audio { ____Placeholder_led_audio } led_audio ;

/* Variables and functions */
 int* audio_state ; 

enum led_brightness ledtrig_audio_get(enum led_audio type)
{
	return audio_state[type];
}