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
typedef  unsigned int uint32_t ;
struct hubp {int dummy; } ;
struct dcn10_hubp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCHUBP_CNTL ; 
 int /*<<< orphan*/  HUBP_UNDERFLOW_STATUS ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct dcn10_hubp* TO_DCN10_HUBP (struct hubp*) ; 

__attribute__((used)) static unsigned int hubp1_get_underflow_status(struct hubp *hubp)
{
	uint32_t hubp_underflow = 0;
	struct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	REG_GET(DCHUBP_CNTL,
		HUBP_UNDERFLOW_STATUS,
		&hubp_underflow);

	return hubp_underflow;
}