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
struct otx2_mbox {int dummy; } ;
struct mbox_msghdr {int dummy; } ;

/* Variables and functions */
 struct mbox_msghdr* otx2_mbox_alloc_msg_rsp (struct otx2_mbox*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct mbox_msghdr *otx2_mbox_alloc_msg(struct otx2_mbox *mbox,
						      int devid, int size)
{
	return otx2_mbox_alloc_msg_rsp(mbox, devid, size, 0);
}