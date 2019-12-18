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
struct tid_info {int hash_base; int ntids; int nstids; int stid_base; int natids; int atids_in_use; int ftid_base; int nftids; int nsftids; int sftid_base; int /*<<< orphan*/  sftids_in_use; scalar_t__ v6_stids_in_use; scalar_t__ stids_in_use; int /*<<< orphan*/  tids_in_use; int /*<<< orphan*/  conns_in_use; int /*<<< orphan*/  hash_tids_in_use; int /*<<< orphan*/  aftid_end; int /*<<< orphan*/  aftid_base; } ;
struct seq_file {struct adapter* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {int flags; struct tid_info tids; TYPE_1__ params; } ;
typedef  enum chip_type { ____Placeholder_chip_type } chip_type ;

/* Variables and functions */
 int CHELSIO_CHIP_VERSION (int /*<<< orphan*/ ) ; 
 int CHELSIO_T5 ; 
 int CXGB4_FW_OFLD_CONN ; 
 int HASHEN_F ; 
 int /*<<< orphan*/  LE_DB_ACTIVE_TABLE_START_INDEX_A ; 
 int /*<<< orphan*/  LE_DB_ACT_CNT_IPV4_A ; 
 int /*<<< orphan*/  LE_DB_ACT_CNT_IPV6_A ; 
 int /*<<< orphan*/  LE_DB_CONFIG_A ; 
 int /*<<< orphan*/  LE_DB_SERVER_INDEX_A ; 
 int /*<<< orphan*/  LE_DB_SRVR_START_INDEX_A ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tid_info_show(struct seq_file *seq, void *v)
{
	unsigned int tid_start = 0;
	struct adapter *adap = seq->private;
	const struct tid_info *t = &adap->tids;
	enum chip_type chip = CHELSIO_CHIP_VERSION(adap->params.chip);

	if (chip > CHELSIO_T5)
		tid_start = t4_read_reg(adap, LE_DB_ACTIVE_TABLE_START_INDEX_A);

	if (t4_read_reg(adap, LE_DB_CONFIG_A) & HASHEN_F) {
		unsigned int sb;
		seq_printf(seq, "Connections in use: %u\n",
			   atomic_read(&t->conns_in_use));

		if (chip <= CHELSIO_T5)
			sb = t4_read_reg(adap, LE_DB_SERVER_INDEX_A) / 4;
		else
			sb = t4_read_reg(adap, LE_DB_SRVR_START_INDEX_A);

		if (sb) {
			seq_printf(seq, "TID range: %u..%u/%u..%u", tid_start,
				   sb - 1, adap->tids.hash_base,
				   t->ntids - 1);
			seq_printf(seq, ", in use: %u/%u\n",
				   atomic_read(&t->tids_in_use),
				   atomic_read(&t->hash_tids_in_use));
		} else if (adap->flags & CXGB4_FW_OFLD_CONN) {
			seq_printf(seq, "TID range: %u..%u/%u..%u",
				   t->aftid_base,
				   t->aftid_end,
				   adap->tids.hash_base,
				   t->ntids - 1);
			seq_printf(seq, ", in use: %u/%u\n",
				   atomic_read(&t->tids_in_use),
				   atomic_read(&t->hash_tids_in_use));
		} else {
			seq_printf(seq, "TID range: %u..%u",
				   adap->tids.hash_base,
				   t->ntids - 1);
			seq_printf(seq, ", in use: %u\n",
				   atomic_read(&t->hash_tids_in_use));
		}
	} else if (t->ntids) {
		seq_printf(seq, "Connections in use: %u\n",
			   atomic_read(&t->conns_in_use));

		seq_printf(seq, "TID range: %u..%u", tid_start,
			   tid_start + t->ntids - 1);
		seq_printf(seq, ", in use: %u\n",
			   atomic_read(&t->tids_in_use));
	}

	if (t->nstids)
		seq_printf(seq, "STID range: %u..%u, in use-IPv4/IPv6: %u/%u\n",
			   (!t->stid_base &&
			   (chip <= CHELSIO_T5)) ?
			   t->stid_base + 1 : t->stid_base,
			   t->stid_base + t->nstids - 1,
			   t->stids_in_use - t->v6_stids_in_use,
			   t->v6_stids_in_use);

	if (t->natids)
		seq_printf(seq, "ATID range: 0..%u, in use: %u\n",
			   t->natids - 1, t->atids_in_use);
	seq_printf(seq, "FTID range: %u..%u\n", t->ftid_base,
		   t->ftid_base + t->nftids - 1);
	if (t->nsftids)
		seq_printf(seq, "SFTID range: %u..%u in use: %u\n",
			   t->sftid_base, t->sftid_base + t->nsftids - 2,
			   t->sftids_in_use);
	if (t->ntids)
		seq_printf(seq, "HW TID usage: %u IP users, %u IPv6 users\n",
			   t4_read_reg(adap, LE_DB_ACT_CNT_IPV4_A),
			   t4_read_reg(adap, LE_DB_ACT_CNT_IPV6_A));
	return 0;
}