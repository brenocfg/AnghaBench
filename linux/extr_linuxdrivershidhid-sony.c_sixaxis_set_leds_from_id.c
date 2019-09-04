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
struct TYPE_4__ {int member_0; int member_1; int member_2; int member_3; } ;
typedef  TYPE_1__ u8 ;
struct sony_sc {int device_id; int /*<<< orphan*/  led_state; } ;
typedef  int /*<<< orphan*/  sixaxis_leds ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (TYPE_1__ const*) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ MAX_LEDS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_1__ const*,int) ; 

__attribute__((used)) static void sixaxis_set_leds_from_id(struct sony_sc *sc)
{
	static const u8 sixaxis_leds[10][4] = {
				{ 0x01, 0x00, 0x00, 0x00 },
				{ 0x00, 0x01, 0x00, 0x00 },
				{ 0x00, 0x00, 0x01, 0x00 },
				{ 0x00, 0x00, 0x00, 0x01 },
				{ 0x01, 0x00, 0x00, 0x01 },
				{ 0x00, 0x01, 0x00, 0x01 },
				{ 0x00, 0x00, 0x01, 0x01 },
				{ 0x01, 0x00, 0x01, 0x01 },
				{ 0x00, 0x01, 0x01, 0x01 },
				{ 0x01, 0x01, 0x01, 0x01 }
	};

	int id = sc->device_id;

	BUILD_BUG_ON(MAX_LEDS < ARRAY_SIZE(sixaxis_leds[0]));

	if (id < 0)
		return;

	id %= 10;
	memcpy(sc->led_state, sixaxis_leds[id], sizeof(sixaxis_leds[id]));
}