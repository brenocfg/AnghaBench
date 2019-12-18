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
struct ath_regulatory {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath_regd_get_eepromRD (struct ath_regulatory*) ; 
 int is_wwr_sku (int /*<<< orphan*/ ) ; 

bool ath_is_world_regd(struct ath_regulatory *reg)
{
	return is_wwr_sku(ath_regd_get_eepromRD(reg));
}