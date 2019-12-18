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
struct ofdpa_port {int /*<<< orphan*/  rocker_port; struct ofdpa* ofdpa; } ;
struct ofdpa_flow_tbl_entry {size_t key_len; int /*<<< orphan*/  cmd; int /*<<< orphan*/  entry; int /*<<< orphan*/  key; int /*<<< orphan*/  key_crc32; } ;
struct ofdpa {int /*<<< orphan*/  flow_tbl_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROCKER_TLV_CMD_TYPE_OF_DPA_FLOW_DEL ; 
 int /*<<< orphan*/  crc32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  hash_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ofdpa_flow_tbl_entry*) ; 
 int /*<<< orphan*/  ofdpa_cmd_flow_tbl_del ; 
 int /*<<< orphan*/  ofdpa_flags_nowait (int) ; 
 struct ofdpa_flow_tbl_entry* ofdpa_flow_tbl_find (struct ofdpa*,struct ofdpa_flow_tbl_entry*) ; 
 int rocker_cmd_exec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ofdpa_flow_tbl_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ofdpa_flow_tbl_del(struct ofdpa_port *ofdpa_port,
			      int flags, struct ofdpa_flow_tbl_entry *match)
{
	struct ofdpa *ofdpa = ofdpa_port->ofdpa;
	struct ofdpa_flow_tbl_entry *found;
	size_t key_len = match->key_len ? match->key_len : sizeof(found->key);
	unsigned long lock_flags;
	int err = 0;

	match->key_crc32 = crc32(~0, &match->key, key_len);

	spin_lock_irqsave(&ofdpa->flow_tbl_lock, lock_flags);

	found = ofdpa_flow_tbl_find(ofdpa, match);

	if (found) {
		hash_del(&found->entry);
		found->cmd = ROCKER_TLV_CMD_TYPE_OF_DPA_FLOW_DEL;
	}

	spin_unlock_irqrestore(&ofdpa->flow_tbl_lock, lock_flags);

	kfree(match);

	if (found) {
		err = rocker_cmd_exec(ofdpa_port->rocker_port,
				      ofdpa_flags_nowait(flags),
				      ofdpa_cmd_flow_tbl_del,
				      found, NULL, NULL);
		kfree(found);
	}

	return err;
}