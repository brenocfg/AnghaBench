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
struct av7110 {int /*<<< orphan*/  video_dev; int /*<<< orphan*/  audio_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_unregister_device (int /*<<< orphan*/ ) ; 

void av7110_av_unregister(struct av7110 *av7110)
{
	dvb_unregister_device(av7110->audio_dev);
	dvb_unregister_device(av7110->video_dev);
}