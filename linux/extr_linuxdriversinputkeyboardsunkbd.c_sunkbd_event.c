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
struct sunkbd {int /*<<< orphan*/  serio; } ;
struct input_dev {int /*<<< orphan*/  led; } ;

/* Variables and functions */
#define  EV_LED 131 
#define  EV_SND 130 
 int /*<<< orphan*/  LED_CAPSL ; 
 int /*<<< orphan*/  LED_COMPOSE ; 
 int /*<<< orphan*/  LED_NUML ; 
 int /*<<< orphan*/  LED_SCROLLL ; 
#define  SND_BELL 129 
#define  SND_CLICK 128 
 int /*<<< orphan*/  SUNKBD_CMD_BELLOFF ; 
 int /*<<< orphan*/  SUNKBD_CMD_NOCLICK ; 
 int SUNKBD_CMD_SETLED ; 
 struct sunkbd* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  serio_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sunkbd_event(struct input_dev *dev,
			unsigned int type, unsigned int code, int value)
{
	struct sunkbd *sunkbd = input_get_drvdata(dev);

	switch (type) {

	case EV_LED:

		serio_write(sunkbd->serio, SUNKBD_CMD_SETLED);
		serio_write(sunkbd->serio,
			(!!test_bit(LED_CAPSL,   dev->led) << 3) |
			(!!test_bit(LED_SCROLLL, dev->led) << 2) |
			(!!test_bit(LED_COMPOSE, dev->led) << 1) |
			 !!test_bit(LED_NUML,    dev->led));
		return 0;

	case EV_SND:

		switch (code) {

		case SND_CLICK:
			serio_write(sunkbd->serio, SUNKBD_CMD_NOCLICK - value);
			return 0;

		case SND_BELL:
			serio_write(sunkbd->serio, SUNKBD_CMD_BELLOFF - value);
			return 0;
		}

		break;
	}

	return -1;
}