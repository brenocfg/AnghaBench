#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct cx88_core {scalar_t__ sd_wm8775; } ;
struct cx88_audio_dev {int /*<<< orphan*/  reg_lock; struct cx88_core* core; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUD_BAL_CTL ; 
 int /*<<< orphan*/  AUD_VOL_CTL ; 
 int /*<<< orphan*/  SHADOW_AUD_VOL_CTL ; 
 int cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_swrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_cx88_wm8775_volume_put (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 
 struct cx88_audio_dev* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_cx88_volume_put(struct snd_kcontrol *kcontrol,
			       struct snd_ctl_elem_value *value)
{
	struct cx88_audio_dev *chip = snd_kcontrol_chip(kcontrol);
	struct cx88_core *core = chip->core;
	int left, right, v, b;
	int changed = 0;
	u32 old;

	if (core->sd_wm8775)
		snd_cx88_wm8775_volume_put(kcontrol, value);

	left = value->value.integer.value[0] & 0x3f;
	right = value->value.integer.value[1] & 0x3f;
	b = right - left;
	if (b < 0) {
		v = 0x3f - left;
		b = (-b) | 0x40;
	} else {
		v = 0x3f - right;
	}
	/* Do we really know this will always be called with IRQs on? */
	spin_lock_irq(&chip->reg_lock);
	old = cx_read(AUD_VOL_CTL);
	if (v != (old & 0x3f)) {
		cx_swrite(SHADOW_AUD_VOL_CTL, AUD_VOL_CTL, (old & ~0x3f) | v);
		changed = 1;
	}
	if ((cx_read(AUD_BAL_CTL) & 0x7f) != b) {
		cx_write(AUD_BAL_CTL, b);
		changed = 1;
	}
	spin_unlock_irq(&chip->reg_lock);

	return changed;
}