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
typedef  int /*<<< orphan*/  u16 ;
struct sky2_port {scalar_t__ speed; int /*<<< orphan*/  port; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  GM_SERIAL_MODE ; 
 int /*<<< orphan*/  GM_SMOD_IPG_MSK ; 
 int /*<<< orphan*/  IPG_DATA_DEF_1000 ; 
 int /*<<< orphan*/  IPG_DATA_DEF_10_100 ; 
 int /*<<< orphan*/  IPG_DATA_VAL (int /*<<< orphan*/ ) ; 
 scalar_t__ SPEED_100 ; 
 int /*<<< orphan*/  gma_read16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gma_write16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sky2_set_ipg(struct sky2_port *sky2)
{
	u16 reg;

	reg = gma_read16(sky2->hw, sky2->port, GM_SERIAL_MODE);
	reg &= ~GM_SMOD_IPG_MSK;
	if (sky2->speed > SPEED_100)
		reg |= IPG_DATA_VAL(IPG_DATA_DEF_1000);
	else
		reg |= IPG_DATA_VAL(IPG_DATA_DEF_10_100);
	gma_write16(sky2->hw, sky2->port, GM_SERIAL_MODE, reg);
}