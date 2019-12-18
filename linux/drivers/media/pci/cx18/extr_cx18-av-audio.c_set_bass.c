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
struct cx18 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx18_av_and_or (struct cx18*,int,int,int) ; 

__attribute__((used)) static void set_bass(struct cx18 *cx, int bass)
{
	/* PATH1_EQ_BASS_VOL */
	cx18_av_and_or(cx, 0x8d9, ~0x3f, 48 - (bass * 48 / 0xffff));
}