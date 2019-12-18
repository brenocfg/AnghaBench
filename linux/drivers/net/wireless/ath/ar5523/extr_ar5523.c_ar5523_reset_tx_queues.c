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
struct ar5523 {int dummy; } ;
typedef  int /*<<< orphan*/  qid ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  WDCMSG_RELEASE_TX_QUEUE ; 
 int ar5523_cmd_write (struct ar5523*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar5523_dbg (struct ar5523*,char*) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ar5523_reset_tx_queues(struct ar5523 *ar)
{
	__be32 qid = cpu_to_be32(0);

	ar5523_dbg(ar, "resetting Tx queue\n");
	return ar5523_cmd_write(ar, WDCMSG_RELEASE_TX_QUEUE,
				 &qid, sizeof(qid), 0);
}