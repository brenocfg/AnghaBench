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
struct ams_delta_nand {int /*<<< orphan*/  gpiod_nwe; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ndelay (int) ; 

__attribute__((used)) static void ams_delta_write_commit(struct ams_delta_nand *priv)
{
	gpiod_set_value(priv->gpiod_nwe, 0);
	ndelay(40);
	gpiod_set_value(priv->gpiod_nwe, 1);
}