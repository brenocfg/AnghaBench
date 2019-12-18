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
struct TYPE_2__ {void* qflags; void* mode; void* bursttime; void* logcwmax; void* logcwmin; void* aifs; void* priority; } ;
struct ar5523_cmd_txq_setup {TYPE_1__ attr; void* len; void* qid; } ;
struct ar5523 {int dummy; } ;
typedef  int /*<<< orphan*/  qinfo ;

/* Variables and functions */
 int /*<<< orphan*/  WDCMSG_SETUP_TX_QUEUE ; 
 int ar5523_cmd_write (struct ar5523*,int /*<<< orphan*/ ,struct ar5523_cmd_txq_setup*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar5523_dbg (struct ar5523*,char*) ; 
 void* cpu_to_be32 (int) ; 

__attribute__((used)) static int ar5523_queue_init(struct ar5523 *ar)
{
	struct ar5523_cmd_txq_setup qinfo;

	ar5523_dbg(ar, "setting up Tx queue\n");
	qinfo.qid	     = cpu_to_be32(0);
	qinfo.len	     = cpu_to_be32(sizeof(qinfo.attr));
	qinfo.attr.priority  = cpu_to_be32(0);	/* XXX */
	qinfo.attr.aifs	     = cpu_to_be32(3);
	qinfo.attr.logcwmin  = cpu_to_be32(4);
	qinfo.attr.logcwmax  = cpu_to_be32(10);
	qinfo.attr.bursttime = cpu_to_be32(0);
	qinfo.attr.mode	     = cpu_to_be32(0);
	qinfo.attr.qflags    = cpu_to_be32(1);	/* XXX? */
	return ar5523_cmd_write(ar, WDCMSG_SETUP_TX_QUEUE, &qinfo,
				 sizeof(qinfo), 0);
}