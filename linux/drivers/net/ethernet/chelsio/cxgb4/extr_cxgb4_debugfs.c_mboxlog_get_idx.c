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
struct seq_file {struct adapter* private; } ;
struct mbox_cmd_log {scalar_t__ size; } ;
struct adapter {struct mbox_cmd_log* mbox_log; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */

__attribute__((used)) static inline void *mboxlog_get_idx(struct seq_file *seq, loff_t pos)
{
	struct adapter *adapter = seq->private;
	struct mbox_cmd_log *log = adapter->mbox_log;

	return ((pos <= log->size) ? (void *)(uintptr_t)(pos + 1) : NULL);
}