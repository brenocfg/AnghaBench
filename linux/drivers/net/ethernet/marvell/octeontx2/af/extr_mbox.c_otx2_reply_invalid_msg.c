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
typedef  void* u16 ;
struct otx2_mbox {int dummy; } ;
struct TYPE_2__ {void* pcifunc; int /*<<< orphan*/  rc; int /*<<< orphan*/  sig; void* id; } ;
struct msg_rsp {TYPE_1__ hdr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MBOX_MSG_INVALID ; 
 int /*<<< orphan*/  OTX2_MBOX_RSP_SIG ; 
 scalar_t__ otx2_mbox_alloc_msg (struct otx2_mbox*,int,int) ; 

int
otx2_reply_invalid_msg(struct otx2_mbox *mbox, int devid, u16 pcifunc, u16 id)
{
	struct msg_rsp *rsp;

	rsp = (struct msg_rsp *)
	       otx2_mbox_alloc_msg(mbox, devid, sizeof(*rsp));
	if (!rsp)
		return -ENOMEM;
	rsp->hdr.id = id;
	rsp->hdr.sig = OTX2_MBOX_RSP_SIG;
	rsp->hdr.rc = MBOX_MSG_INVALID;
	rsp->hdr.pcifunc = pcifunc;
	return 0;
}