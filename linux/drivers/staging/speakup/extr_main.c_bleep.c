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
typedef  int u_short ;
struct TYPE_2__ {short freq; int active; int /*<<< orphan*/  jiffies; } ;

/* Variables and functions */
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int spk_bleep_time ; 
 TYPE_1__ spk_unprocessed_sound ; 

__attribute__((used)) static void bleep(u_short val)
{
	static const short vals[] = {
		350, 370, 392, 414, 440, 466, 491, 523, 554, 587, 619, 659
	};
	short freq;
	int time = spk_bleep_time;

	freq = vals[val % 12];
	if (val > 11)
		freq *= (1 << (val / 12));
	spk_unprocessed_sound.freq = freq;
	spk_unprocessed_sound.jiffies = msecs_to_jiffies(time);
	spk_unprocessed_sound.active = 1;
	/* We can only have 1 active sound at a time. */
}