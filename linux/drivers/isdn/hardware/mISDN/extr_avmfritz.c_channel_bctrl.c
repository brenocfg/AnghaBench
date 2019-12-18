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
struct mISDN_ctrl_req {int dummy; } ;
struct bchannel {int dummy; } ;

/* Variables and functions */
 int mISDN_ctrl_bchannel (struct bchannel*,struct mISDN_ctrl_req*) ; 

__attribute__((used)) static int
channel_bctrl(struct bchannel *bch, struct mISDN_ctrl_req *cq)
{
	return mISDN_ctrl_bchannel(bch, cq);
}