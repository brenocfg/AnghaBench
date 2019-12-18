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
typedef  int u64 ;
typedef  void* u32 ;
typedef  int u16 ;
struct mbox_cmd_log {int size; int cursor; } ;
struct mbox_cmd {scalar_t__ timestamp; int* cmd; } ;
struct cudbg_mbox_log {void** lo; void** hi; int /*<<< orphan*/  entry; } ;
struct cudbg_init {struct adapter* adap; } ;
struct cudbg_error {int dummy; } ;
struct cudbg_buffer {scalar_t__ data; int /*<<< orphan*/  member_0; } ;
struct adapter {struct mbox_cmd_log* mbox_log; } ;

/* Variables and functions */
 int MBOX_LEN ; 
 int cudbg_get_buff (struct cudbg_init*,struct cudbg_buffer*,void*,struct cudbg_buffer*) ; 
 int cudbg_write_and_release_buff (struct cudbg_init*,struct cudbg_buffer*,struct cudbg_buffer*) ; 
 struct mbox_cmd* mbox_cmd_log_entry (struct mbox_cmd_log*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mbox_cmd*,int) ; 

int cudbg_collect_mbox_log(struct cudbg_init *pdbg_init,
			   struct cudbg_buffer *dbg_buff,
			   struct cudbg_error *cudbg_err)
{
	struct adapter *padap = pdbg_init->adap;
	struct cudbg_mbox_log *mboxlog = NULL;
	struct cudbg_buffer temp_buff = { 0 };
	struct mbox_cmd_log *log = NULL;
	struct mbox_cmd *entry;
	unsigned int entry_idx;
	u16 mbox_cmds;
	int i, k, rc;
	u64 flit;
	u32 size;

	log = padap->mbox_log;
	mbox_cmds = padap->mbox_log->size;
	size = sizeof(struct cudbg_mbox_log) * mbox_cmds;
	rc = cudbg_get_buff(pdbg_init, dbg_buff, size, &temp_buff);
	if (rc)
		return rc;

	mboxlog = (struct cudbg_mbox_log *)temp_buff.data;
	for (k = 0; k < mbox_cmds; k++) {
		entry_idx = log->cursor + k;
		if (entry_idx >= log->size)
			entry_idx -= log->size;

		entry = mbox_cmd_log_entry(log, entry_idx);
		/* skip over unused entries */
		if (entry->timestamp == 0)
			continue;

		memcpy(&mboxlog->entry, entry, sizeof(struct mbox_cmd));
		for (i = 0; i < MBOX_LEN / 8; i++) {
			flit = entry->cmd[i];
			mboxlog->hi[i] = (u32)(flit >> 32);
			mboxlog->lo[i] = (u32)flit;
		}
		mboxlog++;
	}
	return cudbg_write_and_release_buff(pdbg_init, &temp_buff, dbg_buff);
}