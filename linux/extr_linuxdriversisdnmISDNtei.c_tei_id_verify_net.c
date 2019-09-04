#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_3__ {int /*<<< orphan*/  (* printdebug ) (struct FsmInst*,char*,int,int) ;} ;
struct teimgr {TYPE_2__* l2; TYPE_1__ tei_m; } ;
struct FsmInst {struct teimgr* userdata; } ;
struct TYPE_4__ {int tei; } ;

/* Variables and functions */
 int DEBUG_L2_TEI ; 
 int* debug ; 
 int /*<<< orphan*/  stub1 (struct FsmInst*,char*,int,int) ; 
 int /*<<< orphan*/  tei_id_chk_req_net (struct FsmInst*,int,void*) ; 

__attribute__((used)) static void
tei_id_verify_net(struct FsmInst *fi, int event, void *arg)
{
	struct teimgr *tm = fi->userdata;
	u_char *dp = arg;
	int tei;

	tei = dp[3] >> 1;
	if (*debug & DEBUG_L2_TEI)
		tm->tei_m.printdebug(fi, "identity verify req tei %d/%d",
				     tei, tm->l2->tei);
	if (tei == tm->l2->tei)
		tei_id_chk_req_net(fi, event, arg);
}