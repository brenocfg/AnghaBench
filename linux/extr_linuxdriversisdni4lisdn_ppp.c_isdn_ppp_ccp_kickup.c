#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ippp_struct {TYPE_1__* lp; } ;
struct TYPE_2__ {int /*<<< orphan*/  ppp_slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPP_COMP ; 
 int /*<<< orphan*/  isdn_ppp_fill_rq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isdn_ppp_ccp_kickup(struct ippp_struct *is)
{
	isdn_ppp_fill_rq(NULL, 0, PPP_COMP, is->lp->ppp_slot);
}