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
typedef  int u32 ;
struct mthca_mailbox {int* buf; int /*<<< orphan*/  dma; } ;
struct mthca_init_ib_param {int vl_cap; int port_width; int mtu_cap; int gid_cap; int pkey_cap; int guid0; int node_guid; int si_guid; scalar_t__ set_si_guid; scalar_t__ set_node_guid; scalar_t__ set_guid0; } ;
struct mthca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INIT_IB ; 
 int /*<<< orphan*/  CMD_TIME_CLASS_A ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_IB_FLAGS_OFFSET ; 
 int INIT_IB_FLAG_G0 ; 
 int INIT_IB_FLAG_NG ; 
 int INIT_IB_FLAG_SIG ; 
 int /*<<< orphan*/  INIT_IB_GUID0_OFFSET ; 
 int /*<<< orphan*/  INIT_IB_IN_SIZE ; 
 int /*<<< orphan*/  INIT_IB_MAX_GID_OFFSET ; 
 int /*<<< orphan*/  INIT_IB_MAX_PKEY_OFFSET ; 
 int INIT_IB_MTU_SHIFT ; 
 int /*<<< orphan*/  INIT_IB_NODE_GUID_OFFSET ; 
 int INIT_IB_PORT_WIDTH_SHIFT ; 
 int /*<<< orphan*/  INIT_IB_SI_GUID_OFFSET ; 
 int INIT_IB_VL_SHIFT ; 
 scalar_t__ IS_ERR (struct mthca_mailbox*) ; 
 int /*<<< orphan*/  MTHCA_PUT (int*,int,int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct mthca_mailbox*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mthca_mailbox* mthca_alloc_mailbox (struct mthca_dev*,int /*<<< orphan*/ ) ; 
 int mthca_cmd (struct mthca_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_free_mailbox (struct mthca_dev*,struct mthca_mailbox*) ; 

int mthca_INIT_IB(struct mthca_dev *dev,
		  struct mthca_init_ib_param *param,
		  int port)
{
	struct mthca_mailbox *mailbox;
	u32 *inbox;
	int err;
	u32 flags;

#define INIT_IB_IN_SIZE          56
#define INIT_IB_FLAGS_OFFSET     0x00
#define INIT_IB_FLAG_SIG         (1 << 18)
#define INIT_IB_FLAG_NG          (1 << 17)
#define INIT_IB_FLAG_G0          (1 << 16)
#define INIT_IB_VL_SHIFT         4
#define INIT_IB_PORT_WIDTH_SHIFT 8
#define INIT_IB_MTU_SHIFT        12
#define INIT_IB_MAX_GID_OFFSET   0x06
#define INIT_IB_MAX_PKEY_OFFSET  0x0a
#define INIT_IB_GUID0_OFFSET     0x10
#define INIT_IB_NODE_GUID_OFFSET 0x18
#define INIT_IB_SI_GUID_OFFSET   0x20

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);
	inbox = mailbox->buf;

	memset(inbox, 0, INIT_IB_IN_SIZE);

	flags = 0;
	flags |= param->set_guid0     ? INIT_IB_FLAG_G0  : 0;
	flags |= param->set_node_guid ? INIT_IB_FLAG_NG  : 0;
	flags |= param->set_si_guid   ? INIT_IB_FLAG_SIG : 0;
	flags |= param->vl_cap << INIT_IB_VL_SHIFT;
	flags |= param->port_width << INIT_IB_PORT_WIDTH_SHIFT;
	flags |= param->mtu_cap << INIT_IB_MTU_SHIFT;
	MTHCA_PUT(inbox, flags, INIT_IB_FLAGS_OFFSET);

	MTHCA_PUT(inbox, param->gid_cap,   INIT_IB_MAX_GID_OFFSET);
	MTHCA_PUT(inbox, param->pkey_cap,  INIT_IB_MAX_PKEY_OFFSET);
	MTHCA_PUT(inbox, param->guid0,     INIT_IB_GUID0_OFFSET);
	MTHCA_PUT(inbox, param->node_guid, INIT_IB_NODE_GUID_OFFSET);
	MTHCA_PUT(inbox, param->si_guid,   INIT_IB_SI_GUID_OFFSET);

	err = mthca_cmd(dev, mailbox->dma, port, 0, CMD_INIT_IB,
			CMD_TIME_CLASS_A);

	mthca_free_mailbox(dev, mailbox);
	return err;
}