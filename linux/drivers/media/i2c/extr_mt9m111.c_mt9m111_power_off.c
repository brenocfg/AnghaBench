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
struct mt9m111 {int /*<<< orphan*/  clk; int /*<<< orphan*/  regulator; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt9m111_suspend (struct mt9m111*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_clk_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mt9m111_power_off(struct mt9m111 *mt9m111)
{
	mt9m111_suspend(mt9m111);
	regulator_disable(mt9m111->regulator);
	v4l2_clk_disable(mt9m111->clk);
}