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
struct input_polled_dev {int /*<<< orphan*/  input; struct gpio_decoder* private; } ;
struct gpio_decoder {int last_stable; int /*<<< orphan*/  axis; } ;

/* Variables and functions */
 int gpio_decoder_get_gpios_state (struct gpio_decoder*) ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gpio_decoder_poll_gpios(struct input_polled_dev *poll_dev)
{
	struct gpio_decoder *decoder = poll_dev->private;
	int state;

	state = gpio_decoder_get_gpios_state(decoder);
	if (state >= 0 && state != decoder->last_stable) {
		input_report_abs(poll_dev->input, decoder->axis, state);
		input_sync(poll_dev->input);
		decoder->last_stable = state;
	}
}