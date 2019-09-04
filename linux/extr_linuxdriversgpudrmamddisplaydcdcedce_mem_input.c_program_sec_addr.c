#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dce_mem_input {int dummy; } ;
struct TYPE_3__ {int low_part; int /*<<< orphan*/  high_part; } ;
typedef  TYPE_1__ PHYSICAL_ADDRESS_LOC ;

/* Variables and functions */
 int /*<<< orphan*/  GRPH_SECONDARY_DFQ_ENABLE ; 
 int /*<<< orphan*/  GRPH_SECONDARY_SURFACE_ADDRESS ; 
 int /*<<< orphan*/  GRPH_SECONDARY_SURFACE_ADDRESS_HIGH ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void program_sec_addr(
	struct dce_mem_input *dce_mi,
	PHYSICAL_ADDRESS_LOC address)
{
	/*high register MUST be programmed first*/
	REG_SET(GRPH_SECONDARY_SURFACE_ADDRESS_HIGH, 0,
		GRPH_SECONDARY_SURFACE_ADDRESS_HIGH,
		address.high_part);

	REG_SET_2(GRPH_SECONDARY_SURFACE_ADDRESS, 0,
		GRPH_SECONDARY_SURFACE_ADDRESS, address.low_part >> 8,
		GRPH_SECONDARY_DFQ_ENABLE, 0);
}