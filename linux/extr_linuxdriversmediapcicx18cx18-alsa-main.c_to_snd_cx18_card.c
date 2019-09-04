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
struct v4l2_device {int dummy; } ;
struct snd_cx18_card {int dummy; } ;
struct TYPE_2__ {struct snd_cx18_card* alsa; } ;

/* Variables and functions */
 TYPE_1__* to_cx18 (struct v4l2_device*) ; 

__attribute__((used)) static inline
struct snd_cx18_card *to_snd_cx18_card(struct v4l2_device *v4l2_dev)
{
	return to_cx18(v4l2_dev)->alsa;
}