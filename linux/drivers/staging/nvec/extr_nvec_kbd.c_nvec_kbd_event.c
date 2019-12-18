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
struct nvec_chip {int dummy; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {struct nvec_chip* nvec; } ;

/* Variables and functions */
 unsigned int EV_LED ; 
 unsigned int EV_REP ; 
 unsigned int LED_CAPSL ; 
 char NVEC_KBD ; 
 char SET_LEDS ; 
 TYPE_1__ keys_dev ; 
 int /*<<< orphan*/  nvec_write_async (struct nvec_chip*,char*,int) ; 

__attribute__((used)) static int nvec_kbd_event(struct input_dev *dev, unsigned int type,
			  unsigned int code, int value)
{
	struct nvec_chip *nvec = keys_dev.nvec;
	char buf[] = { NVEC_KBD, SET_LEDS, 0 };

	if (type == EV_REP)
		return 0;

	if (type != EV_LED)
		return -1;

	if (code != LED_CAPSL)
		return -1;

	buf[2] = !!value;
	nvec_write_async(nvec, buf, sizeof(buf));

	return 0;
}