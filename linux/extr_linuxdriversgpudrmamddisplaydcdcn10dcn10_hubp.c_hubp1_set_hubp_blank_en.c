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
struct dcn10_hubp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCHUBP_CNTL ; 
 int /*<<< orphan*/  HUBP_BLANK_EN ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dcn10_hubp* TO_DCN10_HUBP (struct hubp*) ; 

__attribute__((used)) static void hubp1_set_hubp_blank_en(struct hubp *hubp, bool blank)
{
	struct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
	uint32_t blank_en = blank ? 1 : 0;

	REG_UPDATE(DCHUBP_CNTL, HUBP_BLANK_EN, blank_en);
}