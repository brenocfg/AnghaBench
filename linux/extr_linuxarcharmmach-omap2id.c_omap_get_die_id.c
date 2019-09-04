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
struct omap_die_id {void* id_3; void* id_2; void* id_1; void* id_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_TAP_DIE_ID_0 ; 
 int /*<<< orphan*/  OMAP_TAP_DIE_ID_1 ; 
 int /*<<< orphan*/  OMAP_TAP_DIE_ID_2 ; 
 int /*<<< orphan*/  OMAP_TAP_DIE_ID_3 ; 
 int /*<<< orphan*/  OMAP_TAP_DIE_ID_44XX_0 ; 
 int /*<<< orphan*/  OMAP_TAP_DIE_ID_44XX_1 ; 
 int /*<<< orphan*/  OMAP_TAP_DIE_ID_44XX_2 ; 
 int /*<<< orphan*/  OMAP_TAP_DIE_ID_44XX_3 ; 
 void* read_tap_reg (int /*<<< orphan*/ ) ; 
 scalar_t__ soc_is_dra7xx () ; 
 scalar_t__ soc_is_omap44xx () ; 
 scalar_t__ soc_is_omap54xx () ; 

void omap_get_die_id(struct omap_die_id *odi)
{
	if (soc_is_omap44xx() || soc_is_omap54xx() || soc_is_dra7xx()) {
		odi->id_0 = read_tap_reg(OMAP_TAP_DIE_ID_44XX_0);
		odi->id_1 = read_tap_reg(OMAP_TAP_DIE_ID_44XX_1);
		odi->id_2 = read_tap_reg(OMAP_TAP_DIE_ID_44XX_2);
		odi->id_3 = read_tap_reg(OMAP_TAP_DIE_ID_44XX_3);

		return;
	}
	odi->id_0 = read_tap_reg(OMAP_TAP_DIE_ID_0);
	odi->id_1 = read_tap_reg(OMAP_TAP_DIE_ID_1);
	odi->id_2 = read_tap_reg(OMAP_TAP_DIE_ID_2);
	odi->id_3 = read_tap_reg(OMAP_TAP_DIE_ID_3);
}