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
struct serdes_am654 {int /*<<< orphan*/  rx0_enable; int /*<<< orphan*/  tx0_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX0_DISABLE_STATE ; 
 int /*<<< orphan*/  TX0_DISABLE_STATE ; 
 int regmap_field_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int serdes_am654_disable_txrx(struct serdes_am654 *phy)
{
	int ret;

	/* Disable TX */
	ret = regmap_field_write(phy->tx0_enable, TX0_DISABLE_STATE);
	if (ret)
		return ret;

	/* Disable RX */
	ret = regmap_field_write(phy->rx0_enable, RX0_DISABLE_STATE);
	if (ret)
		return ret;

	return 0;
}