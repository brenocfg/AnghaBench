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
typedef  int uint ;
typedef  int u32 ;
struct brcmf_pub {int /*<<< orphan*/  bus_if; TYPE_1__* proto; } ;
struct brcmf_proto_bcdc_dcmd {void* flags; void* len; void* cmd; } ;
struct brcmf_bcdc {int reqid; struct brcmf_proto_bcdc_dcmd msg; int /*<<< orphan*/  buf; } ;
struct TYPE_2__ {scalar_t__ pd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCDC ; 
 int BCDC_DCMD_ID_SHIFT ; 
 int BCDC_DCMD_IF_MASK ; 
 int BCDC_DCMD_IF_SHIFT ; 
 int BCDC_DCMD_SET ; 
 int BRCMF_TX_IOCTL_MAX_MSG_SIZE ; 
 int brcmf_bus_txctl (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  memset (struct brcmf_proto_bcdc_dcmd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
brcmf_proto_bcdc_msg(struct brcmf_pub *drvr, int ifidx, uint cmd, void *buf,
		     uint len, bool set)
{
	struct brcmf_bcdc *bcdc = (struct brcmf_bcdc *)drvr->proto->pd;
	struct brcmf_proto_bcdc_dcmd *msg = &bcdc->msg;
	u32 flags;

	brcmf_dbg(BCDC, "Enter\n");

	memset(msg, 0, sizeof(struct brcmf_proto_bcdc_dcmd));

	msg->cmd = cpu_to_le32(cmd);
	msg->len = cpu_to_le32(len);
	flags = (++bcdc->reqid << BCDC_DCMD_ID_SHIFT);
	if (set)
		flags |= BCDC_DCMD_SET;
	flags = (flags & ~BCDC_DCMD_IF_MASK) |
		(ifidx << BCDC_DCMD_IF_SHIFT);
	msg->flags = cpu_to_le32(flags);

	if (buf)
		memcpy(bcdc->buf, buf, len);

	len += sizeof(*msg);
	if (len > BRCMF_TX_IOCTL_MAX_MSG_SIZE)
		len = BRCMF_TX_IOCTL_MAX_MSG_SIZE;

	/* Send request */
	return brcmf_bus_txctl(drvr->bus_if, (unsigned char *)&bcdc->msg, len);
}