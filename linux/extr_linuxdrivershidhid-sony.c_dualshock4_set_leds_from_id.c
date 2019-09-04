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
struct TYPE_4__ {int member_0; int member_1; int member_2; } ;
typedef  TYPE_1__ u8 ;
struct sony_sc {int device_id; int /*<<< orphan*/  led_state; } ;
typedef  int /*<<< orphan*/  color_code ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (TYPE_1__ const*) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ MAX_LEDS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_1__ const*,int) ; 

__attribute__((used)) static void dualshock4_set_leds_from_id(struct sony_sc *sc)
{
	/* The first 4 color/index entries match what the PS4 assigns */
	static const u8 color_code[7][3] = {
			/* Blue   */	{ 0x00, 0x00, 0x40 },
			/* Red	  */	{ 0x40, 0x00, 0x00 },
			/* Green  */	{ 0x00, 0x40, 0x00 },
			/* Pink   */	{ 0x20, 0x00, 0x20 },
			/* Orange */	{ 0x02, 0x01, 0x00 },
			/* Teal   */	{ 0x00, 0x01, 0x01 },
			/* White  */	{ 0x01, 0x01, 0x01 }
	};

	int id = sc->device_id;

	BUILD_BUG_ON(MAX_LEDS < ARRAY_SIZE(color_code[0]));

	if (id < 0)
		return;

	id %= 7;
	memcpy(sc->led_state, color_code[id], sizeof(color_code[id]));
}