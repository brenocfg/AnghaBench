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
struct serio {int dummy; } ;
struct TYPE_2__ {unsigned char ibuf; int state; int* channel; size_t offset; } ;
struct fsia6b {TYPE_1__ packet; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int BTN_0 ; 
#define  COLLECT 130 
 int IBUS_SERVO_COUNT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
#define  PROCESS 129 
#define  SYNC 128 
 int /*<<< orphan*/ * fsia6b_axes ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 struct fsia6b* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/ * switch_config ; 

__attribute__((used)) static irqreturn_t fsia6b_serio_irq(struct serio *serio,
				    unsigned char data, unsigned int flags)
{
	struct fsia6b *fsia6b = serio_get_drvdata(serio);
	int i;
	int sw_state;
	int sw_id = BTN_0;

	fsia6b->packet.ibuf = (data << 8) | ((fsia6b->packet.ibuf >> 8) & 0xFF);

	switch (fsia6b->packet.state) {
	case SYNC:
		if (fsia6b->packet.ibuf == 0x4020)
			fsia6b->packet.state = COLLECT;
		break;

	case COLLECT:
		fsia6b->packet.state = PROCESS;
		break;

	case PROCESS:
		fsia6b->packet.channel[fsia6b->packet.offset] =
				fsia6b->packet.ibuf;
		fsia6b->packet.offset++;

		if (fsia6b->packet.offset == IBUS_SERVO_COUNT) {
			fsia6b->packet.offset = 0;
			fsia6b->packet.state = SYNC;
			for (i = 0; i < IBUS_SERVO_COUNT; ++i) {
				input_report_abs(fsia6b->dev, fsia6b_axes[i],
						 fsia6b->packet.channel[i]);

				sw_state = 0;
				if (fsia6b->packet.channel[i] > 1900)
					sw_state = 1;
				else if (fsia6b->packet.channel[i] < 1100)
					sw_state = 2;

				switch (switch_config[i]) {
				case '3':
					input_report_key(fsia6b->dev,
							 sw_id++,
							 sw_state == 0);
					/* fall-through */
				case '2':
					input_report_key(fsia6b->dev,
							 sw_id++,
							 sw_state == 1);
					/* fall-through */
				case '1':
					input_report_key(fsia6b->dev,
							 sw_id++,
							 sw_state == 2);
				}
			}
			input_sync(fsia6b->dev);
		} else {
			fsia6b->packet.state = COLLECT;
		}
		break;
	}

	return IRQ_HANDLED;
}