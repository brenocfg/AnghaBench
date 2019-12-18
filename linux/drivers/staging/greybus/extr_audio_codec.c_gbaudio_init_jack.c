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
struct snd_soc_codec {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  jack; } ;
struct gbaudio_module_info {int jack_mask; int dev_id; int button_mask; int /*<<< orphan*/  dev; TYPE_1__ button_jack; int /*<<< orphan*/  button_name; TYPE_1__ headset_jack; int /*<<< orphan*/  jack_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_MEDIA ; 
 int /*<<< orphan*/  KEY_VOICECOMMAND ; 
 int /*<<< orphan*/  KEY_VOLUMEDOWN ; 
 int /*<<< orphan*/  KEY_VOLUMEUP ; 
 int /*<<< orphan*/  NAME_SIZE ; 
 int SND_JACK_BTN_0 ; 
 int SND_JACK_BTN_1 ; 
 int SND_JACK_BTN_2 ; 
 int SND_JACK_BTN_3 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int snd_jack_set_key (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int snd_soc_jack_new (struct snd_soc_codec*,int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int gbaudio_init_jack(struct gbaudio_module_info *module,
			     struct snd_soc_codec *codec)
{
	int ret;

	if (!module->jack_mask)
		return 0;

	snprintf(module->jack_name, NAME_SIZE, "GB %d Headset Jack",
		 module->dev_id);
	ret = snd_soc_jack_new(codec, module->jack_name, module->jack_mask,
			       &module->headset_jack);
	if (ret) {
		dev_err(module->dev, "Failed to create new jack\n");
		return ret;
	}

	if (!module->button_mask)
		return 0;

	snprintf(module->button_name, NAME_SIZE, "GB %d Button Jack",
		 module->dev_id);
	ret = snd_soc_jack_new(codec, module->button_name, module->button_mask,
			       &module->button_jack);
	if (ret) {
		dev_err(module->dev, "Failed to create button jack\n");
		return ret;
	}

	/*
	 * Currently, max 4 buttons are supported with following key mapping
	 * BTN_0 = KEY_MEDIA
	 * BTN_1 = KEY_VOICECOMMAND
	 * BTN_2 = KEY_VOLUMEUP
	 * BTN_3 = KEY_VOLUMEDOWN
	 */

	if (module->button_mask & SND_JACK_BTN_0) {
		ret = snd_jack_set_key(module->button_jack.jack, SND_JACK_BTN_0,
				       KEY_MEDIA);
		if (ret) {
			dev_err(module->dev, "Failed to set BTN_0\n");
			return ret;
		}
	}

	if (module->button_mask & SND_JACK_BTN_1) {
		ret = snd_jack_set_key(module->button_jack.jack, SND_JACK_BTN_1,
				       KEY_VOICECOMMAND);
		if (ret) {
			dev_err(module->dev, "Failed to set BTN_1\n");
			return ret;
		}
	}

	if (module->button_mask & SND_JACK_BTN_2) {
		ret = snd_jack_set_key(module->button_jack.jack, SND_JACK_BTN_2,
				       KEY_VOLUMEUP);
		if (ret) {
			dev_err(module->dev, "Failed to set BTN_2\n");
			return ret;
		}
	}

	if (module->button_mask & SND_JACK_BTN_3) {
		ret = snd_jack_set_key(module->button_jack.jack, SND_JACK_BTN_3,
				       KEY_VOLUMEDOWN);
		if (ret) {
			dev_err(module->dev, "Failed to set BTN_0\n");
			return ret;
		}
	}

	/* FIXME
	 * verify if this is really required
	set_bit(INPUT_PROP_NO_DUMMY_RELEASE,
		module->button_jack.jack->input_dev->propbit);
	*/

	return 0;
}