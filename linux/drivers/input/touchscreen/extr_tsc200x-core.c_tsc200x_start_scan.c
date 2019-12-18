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
struct tsc200x {int /*<<< orphan*/  dev; int /*<<< orphan*/  (* tsc200x_cmd ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSC200X_CFR0_INITVALUE ; 
 int /*<<< orphan*/  TSC200X_CFR1_INITVALUE ; 
 int /*<<< orphan*/  TSC200X_CFR2_INITVALUE ; 
 int /*<<< orphan*/  TSC200X_CMD_NORMAL ; 
 int /*<<< orphan*/  TSC200X_REG_CFR0 ; 
 int /*<<< orphan*/  TSC200X_REG_CFR1 ; 
 int /*<<< orphan*/  TSC200X_REG_CFR2 ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tsc200x_start_scan(struct tsc200x *ts)
{
	regmap_write(ts->regmap, TSC200X_REG_CFR0, TSC200X_CFR0_INITVALUE);
	regmap_write(ts->regmap, TSC200X_REG_CFR1, TSC200X_CFR1_INITVALUE);
	regmap_write(ts->regmap, TSC200X_REG_CFR2, TSC200X_CFR2_INITVALUE);
	ts->tsc200x_cmd(ts->dev, TSC200X_CMD_NORMAL);
}