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
struct mm_struct {int dummy; } ;
struct cxl_calls {int /*<<< orphan*/  (* cxl_slbia ) (struct mm_struct*) ;} ;

/* Variables and functions */
 struct cxl_calls* cxl_calls_get () ; 
 int /*<<< orphan*/  cxl_calls_put (struct cxl_calls*) ; 
 scalar_t__ cxl_ctx_in_use () ; 
 int /*<<< orphan*/  stub1 (struct mm_struct*) ; 

void cxl_slbia(struct mm_struct *mm)
{
	struct cxl_calls *calls;

	calls = cxl_calls_get();
	if (!calls)
		return;

	if (cxl_ctx_in_use())
	    calls->cxl_slbia(mm);

	cxl_calls_put(calls);
}