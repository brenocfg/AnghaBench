#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
struct TYPE_6__ {TYPE_1__ radio; int /*<<< orphan*/  tuner_type; } ;
struct cx88_core {TYPE_2__ board; } ;
struct TYPE_7__ {char* name; scalar_t__ fm; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  CX88_RADIO ; 
 TYPE_3__* gdi_tuner ; 
 int /*<<< orphan*/  pr_info (char*,char const*) ; 

__attribute__((used)) static void gdi_eeprom(struct cx88_core *core, u8 *eeprom_data)
{
	const char *name = (eeprom_data[0x0d] < ARRAY_SIZE(gdi_tuner))
		? gdi_tuner[eeprom_data[0x0d]].name : NULL;

	pr_info("GDI: tuner=%s\n", name ? name : "unknown");
	if (!name)
		return;
	core->board.tuner_type = gdi_tuner[eeprom_data[0x0d]].id;
	core->board.radio.type = gdi_tuner[eeprom_data[0x0d]].fm ?
		CX88_RADIO : 0;
}