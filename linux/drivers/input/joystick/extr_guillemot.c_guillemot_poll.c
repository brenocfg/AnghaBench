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
typedef  int u8 ;
struct input_dev {int dummy; } ;
struct guillemot {TYPE_1__* type; int /*<<< orphan*/  bads; int /*<<< orphan*/  gameport; int /*<<< orphan*/  reads; struct input_dev* dev; } ;
struct gameport {int dummy; } ;
struct TYPE_4__ {int x; int y; } ;
struct TYPE_3__ {scalar_t__* abs; scalar_t__* btn; scalar_t__ hat; } ;

/* Variables and functions */
 scalar_t__ ABS_HAT0X ; 
 scalar_t__ ABS_HAT0Y ; 
 int GUILLEMOT_MAX_LENGTH ; 
 struct guillemot* gameport_get_drvdata (struct gameport*) ; 
 TYPE_2__* guillemot_hat_to_axis ; 
 int guillemot_read_packet (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void guillemot_poll(struct gameport *gameport)
{
	struct guillemot *guillemot = gameport_get_drvdata(gameport);
	struct input_dev *dev = guillemot->dev;
	u8 data[GUILLEMOT_MAX_LENGTH];
	int i;

	guillemot->reads++;

	if (guillemot_read_packet(guillemot->gameport, data) != GUILLEMOT_MAX_LENGTH * 8 ||
		data[0] != 0x55 || data[16] != 0xaa) {
		guillemot->bads++;
	} else {

		for (i = 0; i < 6 && guillemot->type->abs[i] >= 0; i++)
			input_report_abs(dev, guillemot->type->abs[i], data[i + 5]);

		if (guillemot->type->hat) {
			input_report_abs(dev, ABS_HAT0X, guillemot_hat_to_axis[data[4] >> 4].x);
			input_report_abs(dev, ABS_HAT0Y, guillemot_hat_to_axis[data[4] >> 4].y);
		}

		for (i = 0; i < 16 && guillemot->type->btn[i] >= 0; i++)
			input_report_key(dev, guillemot->type->btn[i], (data[2 + (i >> 3)] >> (i & 7)) & 1);
	}

	input_sync(dev);
}