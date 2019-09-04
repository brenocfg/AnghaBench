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
struct sk_buff {int dummy; } ;
struct capi_ctr {int cnr; } ;
struct TYPE_2__ {scalar_t__* listen_req; int /*<<< orphan*/  rp; } ;

/* Variables and functions */
 int CAPI_MAXAPPL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int _hycapi_appCheck (int,int) ; 
 TYPE_1__* hycapi_applications ; 
 int /*<<< orphan*/  hycapi_register_internal (struct capi_ctr*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hycapi_sendmsg_internal (struct capi_ctr*,struct sk_buff*) ; 
 struct sk_buff* skb_copy (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hycapi_restart_internal(struct capi_ctr *ctrl)
{
	int i;
	struct sk_buff *skb;
#ifdef HYCAPI_PRINTFNAMES
	printk(KERN_WARNING "HYSDN: hycapi_restart_internal");
#endif
	for (i = 0; i < CAPI_MAXAPPL; i++) {
		if (_hycapi_appCheck(i + 1, ctrl->cnr) == 1) {
			hycapi_register_internal(ctrl, i + 1,
						 &hycapi_applications[i].rp);
			if (hycapi_applications[i].listen_req[ctrl->cnr - 1]) {
				skb = skb_copy(hycapi_applications[i].listen_req[ctrl->cnr - 1], GFP_ATOMIC);
				hycapi_sendmsg_internal(ctrl, skb);
			}
		}
	}
}