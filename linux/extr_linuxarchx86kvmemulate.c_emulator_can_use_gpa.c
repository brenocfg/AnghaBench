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
struct x86_emulate_ctxt {int d; scalar_t__ rep_prefix; } ;

/* Variables and functions */
 int String ; 
 int TwoMemOp ; 

bool emulator_can_use_gpa(struct x86_emulate_ctxt *ctxt)
{
	if (ctxt->rep_prefix && (ctxt->d & String))
		return false;

	if (ctxt->d & TwoMemOp)
		return false;

	return true;
}