#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct solo_dev {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_5__ {scalar_t__* value; } ;
struct TYPE_6__ {TYPE_2__ integer; } ;
struct TYPE_4__ {scalar_t__ numid; } ;
struct snd_ctl_elem_value {TYPE_3__ value; TYPE_1__ id; } ;

/* Variables and functions */
 struct solo_dev* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 scalar_t__ tw28_get_audio_gain (struct solo_dev*,scalar_t__) ; 
 int /*<<< orphan*/  tw28_set_audio_gain (struct solo_dev*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int snd_solo_capture_volume_put(struct snd_kcontrol *kcontrol,
				       struct snd_ctl_elem_value *value)
{
	struct solo_dev *solo_dev = snd_kcontrol_chip(kcontrol);
	u8 ch = value->id.numid - 1;
	u8 old_val;

	old_val = tw28_get_audio_gain(solo_dev, ch);
	if (old_val == value->value.integer.value[0])
		return 0;

	tw28_set_audio_gain(solo_dev, ch, value->value.integer.value[0]);

	return 1;
}