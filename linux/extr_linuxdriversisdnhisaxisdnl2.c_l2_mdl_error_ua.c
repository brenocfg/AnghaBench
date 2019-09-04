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
struct TYPE_2__ {int /*<<< orphan*/  (* layer ) (struct PStack*,int,void*) ;} ;
struct PStack {TYPE_1__ ma; } ;
struct FsmInst {struct PStack* userdata; } ;

/* Variables and functions */
 int INDICATION ; 
 int MDL_ERROR ; 
 scalar_t__ get_PollFlagFree (struct PStack*,struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct PStack*,int,void*) ; 
 int /*<<< orphan*/  stub2 (struct PStack*,int,void*) ; 

__attribute__((used)) static void
l2_mdl_error_ua(struct FsmInst *fi, int event, void *arg)
{
	struct sk_buff *skb = arg;
	struct PStack *st = fi->userdata;

	if (get_PollFlagFree(st, skb))
		st->ma.layer(st, MDL_ERROR | INDICATION, (void *) 'C');
	else
		st->ma.layer(st, MDL_ERROR | INDICATION, (void *) 'D');
}