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
struct gbaudio_module_info {int jack_type; int button_mask; int jack_mask; TYPE_1__ headset_jack; int /*<<< orphan*/  dev; scalar_t__ button_status; TYPE_1__ button_jack; } ;
struct gb_audio_jack_event_request {int jack_attribute; int event; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ GB_AUDIO_JACK_EVENT_REMOVAL ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_warn_ratelimited (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  snd_soc_jack_report (TYPE_1__*,int,int) ; 

__attribute__((used)) static int gbaudio_request_jack(struct gbaudio_module_info *module,
				struct gb_audio_jack_event_request *req)
{
	int report;
	struct snd_jack *jack = module->headset_jack.jack;
	struct snd_jack *btn_jack = module->button_jack.jack;

	if (!jack) {
		dev_err_ratelimited(module->dev,
				    "Invalid jack event received:type: %u, event: %u\n",
				    req->jack_attribute, req->event);
		return -EINVAL;
	}

	dev_warn_ratelimited(module->dev,
			     "Jack Event received: type: %u, event: %u\n",
			     req->jack_attribute, req->event);

	if (req->event == GB_AUDIO_JACK_EVENT_REMOVAL) {
		module->jack_type = 0;
		if (btn_jack && module->button_status) {
			snd_soc_jack_report(&module->button_jack, 0,
					    module->button_mask);
			module->button_status = 0;
		}
		snd_soc_jack_report(&module->headset_jack, 0,
				    module->jack_mask);
		return 0;
	}

	report = req->jack_attribute & module->jack_mask;
	if (!report) {
		dev_err_ratelimited(module->dev,
				    "Invalid jack event received:type: %u, event: %u\n",
				    req->jack_attribute, req->event);
		return -EINVAL;
	}

	if (module->jack_type)
		dev_warn_ratelimited(module->dev,
				     "Modifying jack from %d to %d\n",
				     module->jack_type, report);

	module->jack_type = report;
	snd_soc_jack_report(&module->headset_jack, report, module->jack_mask);

	return 0;
}