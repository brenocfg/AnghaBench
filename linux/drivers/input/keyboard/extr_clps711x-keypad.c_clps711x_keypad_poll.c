#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct input_polled_dev {TYPE_1__* input; struct clps711x_keypad_data* private; } ;
struct clps711x_keypad_data {int row_count; int /*<<< orphan*/  syscon; int /*<<< orphan*/  row_shift; struct clps711x_gpio_data* gpio_data; } ;
struct clps711x_gpio_data {int /*<<< orphan*/  last_state; int /*<<< orphan*/  desc; } ;
struct TYPE_4__ {unsigned short* keycode; } ;

/* Variables and functions */
 int CLPS711X_KEYPAD_COL_COUNT ; 
 int /*<<< orphan*/  EV_MSC ; 
 int MATRIX_SCAN_CODE (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  SYSCON1_KBDSCAN (int) ; 
 int /*<<< orphan*/  SYSCON1_KBDSCAN_MASK ; 
 int /*<<< orphan*/  SYSCON_OFFSET ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int gpiod_get_value_cansleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_event (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (TYPE_1__*,unsigned short const,int) ; 
 int /*<<< orphan*/  input_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clps711x_keypad_poll(struct input_polled_dev *dev)
{
	const unsigned short *keycodes = dev->input->keycode;
	struct clps711x_keypad_data *priv = dev->private;
	bool sync = false;
	int col, row;

	for (col = 0; col < CLPS711X_KEYPAD_COL_COUNT; col++) {
		/* Assert column */
		regmap_update_bits(priv->syscon, SYSCON_OFFSET,
				   SYSCON1_KBDSCAN_MASK,
				   SYSCON1_KBDSCAN(8 + col));

		/* Scan rows */
		for (row = 0; row < priv->row_count; row++) {
			struct clps711x_gpio_data *data = &priv->gpio_data[row];
			bool state, state1;

			/* Read twice for protection against fluctuations */
			do {
				state = gpiod_get_value_cansleep(data->desc);
				cond_resched();
				state1 = gpiod_get_value_cansleep(data->desc);
			} while (state != state1);

			if (test_bit(col, data->last_state) != state) {
				int code = MATRIX_SCAN_CODE(row, col,
							    priv->row_shift);

				if (state) {
					set_bit(col, data->last_state);
					input_event(dev->input, EV_MSC,
						    MSC_SCAN, code);
				} else {
					clear_bit(col, data->last_state);
				}

				if (keycodes[code])
					input_report_key(dev->input,
							 keycodes[code], state);
				sync = true;
			}
		}

		/* Set all columns to low */
		regmap_update_bits(priv->syscon, SYSCON_OFFSET,
				   SYSCON1_KBDSCAN_MASK, SYSCON1_KBDSCAN(1));
	}

	if (sync)
		input_sync(dev->input);
}