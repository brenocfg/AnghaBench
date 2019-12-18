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
typedef  int /*<<< orphan*/  u8 ;
struct lp8788_charger {int /*<<< orphan*/  lp; } ;

/* Variables and functions */
 int /*<<< orphan*/  LP8788_CHG_INPUT_STATE_M ; 
 int /*<<< orphan*/  LP8788_CHG_STATUS ; 
 int /*<<< orphan*/  LP8788_FULL_FUNCTION ; 
 int /*<<< orphan*/  LP8788_SYSTEM_SUPPLY ; 
 int /*<<< orphan*/  lp8788_read_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool lp8788_is_charger_detected(struct lp8788_charger *pchg)
{
	u8 data;

	lp8788_read_byte(pchg->lp, LP8788_CHG_STATUS, &data);
	data &= LP8788_CHG_INPUT_STATE_M;

	return data == LP8788_SYSTEM_SUPPLY || data == LP8788_FULL_FUNCTION;
}