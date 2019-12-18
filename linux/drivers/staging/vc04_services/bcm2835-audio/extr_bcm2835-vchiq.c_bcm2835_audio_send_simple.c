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
struct vc_audio_msg {int type; } ;
struct bcm2835_audio_instance {int dummy; } ;

/* Variables and functions */
 int bcm2835_audio_send_msg (struct bcm2835_audio_instance*,struct vc_audio_msg*,int) ; 

__attribute__((used)) static int bcm2835_audio_send_simple(struct bcm2835_audio_instance *instance,
				     int type, bool wait)
{
	struct vc_audio_msg m = { .type = type };

	return bcm2835_audio_send_msg(instance, &m, wait);
}