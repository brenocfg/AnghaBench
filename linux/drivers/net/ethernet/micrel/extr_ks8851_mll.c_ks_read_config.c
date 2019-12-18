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
typedef  int u16 ;
struct ks_net {int sharedbus; int extra_byte; int /*<<< orphan*/  bus_width; } ;

/* Variables and functions */
 int CCR_16BIT ; 
 int CCR_8BIT ; 
 int CCR_SHARED ; 
 int /*<<< orphan*/  ENUM_BUS_16BIT ; 
 int /*<<< orphan*/  ENUM_BUS_32BIT ; 
 int /*<<< orphan*/  ENUM_BUS_8BIT ; 
 scalar_t__ KS_CCR ; 
 int ks_rdreg8 (struct ks_net*,scalar_t__) ; 

__attribute__((used)) static void ks_read_config(struct ks_net *ks)
{
	u16 reg_data = 0;

	/* Regardless of bus width, 8 bit read should always work.*/
	reg_data = ks_rdreg8(ks, KS_CCR) & 0x00FF;
	reg_data |= ks_rdreg8(ks, KS_CCR+1) << 8;

	/* addr/data bus are multiplexed */
	ks->sharedbus = (reg_data & CCR_SHARED) == CCR_SHARED;

	/* There are garbage data when reading data from QMU,
	depending on bus-width.
	*/

	if (reg_data & CCR_8BIT) {
		ks->bus_width = ENUM_BUS_8BIT;
		ks->extra_byte = 1;
	} else if (reg_data & CCR_16BIT) {
		ks->bus_width = ENUM_BUS_16BIT;
		ks->extra_byte = 2;
	} else {
		ks->bus_width = ENUM_BUS_32BIT;
		ks->extra_byte = 4;
	}
}