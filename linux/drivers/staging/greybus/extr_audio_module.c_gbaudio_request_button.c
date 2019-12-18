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
struct snd_jack {int dummy; } ;
struct TYPE_2__ {struct snd_jack* jack; } ;
struct gbaudio_module_info {int button_status; int button_mask; TYPE_1__ button_jack; int /*<<< orphan*/  dev; int /*<<< orphan*/  jack_type; } ;
struct gb_audio_button_event_request {int button_id; scalar_t__ event; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ GB_AUDIO_BUTTON_EVENT_PRESS ; 
 int SND_JACK_BTN_0 ; 
 int SND_JACK_BTN_1 ; 
 int SND_JACK_BTN_2 ; 
 int SND_JACK_BTN_3 ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_warn_ratelimited (int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  snd_soc_jack_report (TYPE_1__*,int,int) ; 

__attribute__((used)) static int gbaudio_request_button(struct gbaudio_module_info *module,
				  struct gb_audio_button_event_request *req)
{
	int soc_button_id, report;
	struct snd_jack *btn_jack = module->button_jack.jack;

	if (!btn_jack) {
		dev_err_ratelimited(module->dev,
				    "Invalid button event received:type: %u, event: %u\n",
				    req->button_id, req->event);
		return -EINVAL;
	}

	dev_warn_ratelimited(module->dev,
			     "Button Event received: id: %u, event: %u\n",
			     req->button_id, req->event);

	/* currently supports 4 buttons only */
	if (!module->jack_type) {
		dev_err_ratelimited(module->dev,
				    "Jack not present. Bogus event!!\n");
		return -EINVAL;
	}

	report = module->button_status & module->button_mask;
	soc_button_id = 0;

	switch (req->button_id) {
	case 1:
		soc_button_id = SND_JACK_BTN_0 & module->button_mask;
		break;

	case 2:
		soc_button_id = SND_JACK_BTN_1 & module->button_mask;
		break;

	case 3:
		soc_button_id = SND_JACK_BTN_2 & module->button_mask;
		break;

	case 4:
		soc_button_id = SND_JACK_BTN_3 & module->button_mask;
		break;
	}

	if (!soc_button_id) {
		dev_err_ratelimited(module->dev,
				    "Invalid button request received\n");
		return -EINVAL;
	}

	if (req->event == GB_AUDIO_BUTTON_EVENT_PRESS)
		report = report | soc_button_id;
	else
		report = report & ~soc_button_id;

	module->button_status = report;

	snd_soc_jack_report(&module->button_jack, report, module->button_mask);

	return 0;
}