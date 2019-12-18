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
typedef  int u8 ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct jornadakbd {int /*<<< orphan*/ * keymap; struct input_dev* input; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  GETSCANKEYCODE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 scalar_t__ TXDUMMY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int jornada_ssp_byte (scalar_t__) ; 
 int /*<<< orphan*/  jornada_ssp_end () ; 
 scalar_t__ jornada_ssp_inout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jornada_ssp_start () ; 
 struct jornadakbd* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static irqreturn_t jornada720_kbd_interrupt(int irq, void *dev_id)
{
	struct platform_device *pdev = dev_id;
	struct jornadakbd *jornadakbd = platform_get_drvdata(pdev);
	struct input_dev *input = jornadakbd->input;
	u8 count, kbd_data, scan_code;

	/* startup ssp with spinlock */
	jornada_ssp_start();

	if (jornada_ssp_inout(GETSCANKEYCODE) != TXDUMMY) {
		dev_dbg(&pdev->dev,
			"GetKeycode command failed with ETIMEDOUT, flushed bus\n");
	} else {
		/* How many keycodes are waiting for us? */
		count = jornada_ssp_byte(TXDUMMY);

		/* Lets drag them out one at a time */
		while (count--) {
			/* Exchange TxDummy for location (keymap[kbddata]) */
			kbd_data = jornada_ssp_byte(TXDUMMY);
			scan_code = kbd_data & 0x7f;

			input_event(input, EV_MSC, MSC_SCAN, scan_code);
			input_report_key(input, jornadakbd->keymap[scan_code],
					 !(kbd_data & 0x80));
			input_sync(input);
		}
	}

	/* release spinlock and turn off ssp */
	jornada_ssp_end();

	return IRQ_HANDLED;
}