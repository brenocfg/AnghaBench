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
typedef  int /*<<< orphan*/  uint ;
struct adb_request {int nbytes; int sent; scalar_t__* data; } ;
struct adb_iopmsg {int count; int /*<<< orphan*/  cmd; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  amsg ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  ADB_CHAN ; 
 int /*<<< orphan*/  ADB_IOP ; 
 int /*<<< orphan*/  ADB_IOP_EXPLICIT ; 
 int /*<<< orphan*/  adb_iop_complete ; 
 int /*<<< orphan*/  adb_iop_state ; 
 struct adb_request* current_req ; 
 int /*<<< orphan*/  iop_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct adb_request*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  sending ; 

__attribute__((used)) static void adb_iop_start(void)
{
	unsigned long flags;
	struct adb_request *req;
	struct adb_iopmsg amsg;
#ifdef DEBUG_ADB_IOP
	int i;
#endif

	/* get the packet to send */
	req = current_req;
	if (!req)
		return;

	local_irq_save(flags);

#ifdef DEBUG_ADB_IOP
	printk("adb_iop_start %p: sending packet, %d bytes:", req, req->nbytes);
	for (i = 0; i < req->nbytes; i++)
		printk(" %02X", (uint)req->data[i]);
	printk("\n");
#endif

	/* The IOP takes MacII-style packets, so */
	/* strip the initial ADB_PACKET byte.    */

	amsg.flags = ADB_IOP_EXPLICIT;
	amsg.count = req->nbytes - 2;

	/* amsg.data immediately follows amsg.cmd, effectively making */
	/* amsg.cmd a pointer to the beginning of a full ADB packet.  */
	memcpy(&amsg.cmd, req->data + 1, req->nbytes - 1);

	req->sent = 1;
	adb_iop_state = sending;
	local_irq_restore(flags);

	/* Now send it. The IOP manager will call adb_iop_complete */
	/* when the packet has been sent.                          */

	iop_send_message(ADB_IOP, ADB_CHAN, req, sizeof(amsg), (__u8 *)&amsg,
			 adb_iop_complete);
}