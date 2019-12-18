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
typedef  int uint32_t ;
struct hubp {int dummy; } ;
struct dcn20_hubp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMDATA_SW_DATA ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int const) ; 
 struct dcn20_hubp* TO_DCN20_HUBP (struct hubp*) ; 

void hubp2_dmdata_load(
		struct hubp *hubp,
		uint32_t dmdata_sw_size,
		const uint32_t *dmdata_sw_data)
{
	int i;
	struct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	/* load dmdata into HUBP buffer in SW mode */
	for (i = 0; i < dmdata_sw_size / 4; i++)
		REG_WRITE(DMDATA_SW_DATA, dmdata_sw_data[i]);
}