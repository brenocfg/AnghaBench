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
struct hubp {int dummy; } ;
struct dcn21_hubp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HUBPREQ_DEBUG ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 struct dcn21_hubp* TO_DCN21_HUBP (struct hubp*) ; 

void hubp21_init(struct hubp *hubp)
{
	// DEDCN21-133: Inconsistent row starting line for flip between DPTE and Meta
	// This is a chicken bit to enable the ECO fix.

	struct dcn21_hubp *hubp21 = TO_DCN21_HUBP(hubp);
	//hubp[i].HUBPREQ_DEBUG.HUBPREQ_DEBUG[26] = 1;
	REG_WRITE(HUBPREQ_DEBUG, 1 << 26);
}