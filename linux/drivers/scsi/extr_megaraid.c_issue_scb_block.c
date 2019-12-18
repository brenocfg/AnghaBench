#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
typedef  int u8 ;
struct mbox_out {int dummy; } ;
struct TYPE_18__ {int busy; int ack; int numstatus; int status; scalar_t__ poll; } ;
struct TYPE_17__ {int cmdid; int xferaddr; } ;
struct TYPE_20__ {TYPE_2__ m_in; TYPE_1__ m_out; } ;
typedef  TYPE_4__ mbox_t ;
struct TYPE_21__ {int xfer_segment_lo; int /*<<< orphan*/  xfer_segment_hi; } ;
typedef  TYPE_5__ mbox64_t ;
struct TYPE_22__ {int flag; int mbox_dma; TYPE_3__* dev; TYPE_4__* mbox; TYPE_5__* mbox64; } ;
typedef  TYPE_6__ adapter_t ;
struct TYPE_19__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BOARD_MEMMAP ; 
 int INTR_VALID ; 
#define  MEGA_MBOXCMD_EXTPTHRU 131 
#define  MEGA_MBOXCMD_LREAD64 130 
#define  MEGA_MBOXCMD_LWRITE64 129 
#define  MEGA_MBOXCMD_PASSTHRU64 128 
 int RDINDOOR (TYPE_6__*) ; 
 int /*<<< orphan*/  WRINDOOR (TYPE_6__*,int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  irq_ack (TYPE_6__*) ; 
 int /*<<< orphan*/  irq_disable (TYPE_6__*) ; 
 int /*<<< orphan*/  irq_enable (TYPE_6__*) ; 
 int irq_state (TYPE_6__*) ; 
 int /*<<< orphan*/  issue_command (TYPE_6__*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ mega_busywait_mbox (TYPE_6__*) ; 
 int /*<<< orphan*/  memcpy (char*,int*,int) ; 
 int /*<<< orphan*/  set_irq_state (TYPE_6__*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
issue_scb_block(adapter_t *adapter, u_char *raw_mbox)
{
	volatile mbox64_t *mbox64 = adapter->mbox64;
	volatile mbox_t *mbox = adapter->mbox;
	u8	byte;

	/* Wait until mailbox is free */
	if(mega_busywait_mbox (adapter))
		goto bug_blocked_mailbox;

	/* Copy mailbox data into host structure */
	memcpy((char *) mbox, raw_mbox, sizeof(struct mbox_out));
	mbox->m_out.cmdid = 0xFE;
	mbox->m_in.busy = 1;

	switch (raw_mbox[0]) {
	case MEGA_MBOXCMD_LREAD64:
	case MEGA_MBOXCMD_LWRITE64:
	case MEGA_MBOXCMD_PASSTHRU64:
	case MEGA_MBOXCMD_EXTPTHRU:
		mbox64->xfer_segment_lo = mbox->m_out.xferaddr;
		mbox64->xfer_segment_hi = 0;
		mbox->m_out.xferaddr = 0xFFFFFFFF;
		break;
	default:
		mbox64->xfer_segment_lo = 0;
		mbox64->xfer_segment_hi = 0;
	}

	if( likely(adapter->flag & BOARD_MEMMAP) ) {
		mbox->m_in.poll = 0;
		mbox->m_in.ack = 0;
		mbox->m_in.numstatus = 0xFF;
		mbox->m_in.status = 0xFF;
		WRINDOOR(adapter, adapter->mbox_dma | 0x1);

		while((volatile u8)mbox->m_in.numstatus == 0xFF)
			cpu_relax();

		mbox->m_in.numstatus = 0xFF;

		while( (volatile u8)mbox->m_in.poll != 0x77 )
			cpu_relax();

		mbox->m_in.poll = 0;
		mbox->m_in.ack = 0x77;

		WRINDOOR(adapter, adapter->mbox_dma | 0x2);

		while(RDINDOOR(adapter) & 0x2)
			cpu_relax();
	}
	else {
		irq_disable(adapter);
		issue_command(adapter);

		while (!((byte = irq_state(adapter)) & INTR_VALID))
			cpu_relax();

		set_irq_state(adapter, byte);
		irq_enable(adapter);
		irq_ack(adapter);
	}

	return mbox->m_in.status;

bug_blocked_mailbox:
	dev_warn(&adapter->dev->dev, "Blocked mailbox......!!\n");
	udelay (1000);
	return -1;
}