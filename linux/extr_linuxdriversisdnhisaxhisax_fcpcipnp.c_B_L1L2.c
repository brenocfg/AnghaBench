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
struct hisax_if {int /*<<< orphan*/  (* l1l2 ) (struct hisax_if*,int,void*) ;} ;
struct fritz_bcs {int /*<<< orphan*/  b_if; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct hisax_if*,int,void*) ; 

__attribute__((used)) static inline void B_L1L2(struct fritz_bcs *bcs, int pr, void *arg)
{
	struct hisax_if *ifc = (struct hisax_if *) &bcs->b_if;

	DBG(2, "pr %#x", pr);
	ifc->l1l2(ifc, pr, arg);
}