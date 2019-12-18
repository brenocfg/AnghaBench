#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  ctx; } ;
struct dce_mem_input {TYPE_1__ base; } ;
struct TYPE_5__ {int high_part; int low_part; } ;
typedef  TYPE_2__ PHYSICAL_ADDRESS_LOC ;

/* Variables and functions */
 int /*<<< orphan*/  GRPH_PRIMARY_SURFACE_ADDRESS_HIGH_L ; 
 int /*<<< orphan*/  GRPH_PRIMARY_SURFACE_ADDRESS_L ; 
 int /*<<< orphan*/  UNP_GRPH_PRIMARY_SURFACE_ADDRESS_HIGH_L ; 
 int UNP_GRPH_PRIMARY_SURFACE_ADDRESS_HIGH_L__GRPH_PRIMARY_SURFACE_ADDRESS_HIGH_L_MASK ; 
 int /*<<< orphan*/  UNP_GRPH_PRIMARY_SURFACE_ADDRESS_L ; 
 int UNP_GRPH_PRIMARY_SURFACE_ADDRESS_L__GRPH_PRIMARY_SURFACE_ADDRESS_L__SHIFT ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmUNP_GRPH_PRIMARY_SURFACE_ADDRESS_HIGH_L ; 
 int /*<<< orphan*/  mmUNP_GRPH_PRIMARY_SURFACE_ADDRESS_L ; 
 int /*<<< orphan*/  set_reg_field_value (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void program_pri_addr_l(
	struct dce_mem_input *mem_input110,
	PHYSICAL_ADDRESS_LOC address)
{
	uint32_t value = 0;
	uint32_t temp = 0;

	/*high register MUST be programmed first*/
	temp = address.high_part &
UNP_GRPH_PRIMARY_SURFACE_ADDRESS_HIGH_L__GRPH_PRIMARY_SURFACE_ADDRESS_HIGH_L_MASK;

	set_reg_field_value(value, temp,
		UNP_GRPH_PRIMARY_SURFACE_ADDRESS_HIGH_L,
		GRPH_PRIMARY_SURFACE_ADDRESS_HIGH_L);

	dm_write_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_PRIMARY_SURFACE_ADDRESS_HIGH_L,
		value);

	temp = 0;
	value = 0;
	temp = address.low_part >>
	UNP_GRPH_PRIMARY_SURFACE_ADDRESS_L__GRPH_PRIMARY_SURFACE_ADDRESS_L__SHIFT;

	set_reg_field_value(value, temp,
		UNP_GRPH_PRIMARY_SURFACE_ADDRESS_L,
		GRPH_PRIMARY_SURFACE_ADDRESS_L);

	dm_write_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_PRIMARY_SURFACE_ADDRESS_L,
		value);
}