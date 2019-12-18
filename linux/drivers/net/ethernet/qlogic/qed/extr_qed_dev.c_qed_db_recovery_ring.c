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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct qed_hwfn {int /*<<< orphan*/  cdev; } ;
struct qed_db_recovery_entry {scalar_t__ db_width; scalar_t__ db_data; int /*<<< orphan*/  db_addr; } ;

/* Variables and functions */
 scalar_t__ DB_REC_WIDTH_32B ; 
 int /*<<< orphan*/  DIRECT_REG_WR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIRECT_REG_WR64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QED_MSG_SPQ ; 
 int /*<<< orphan*/  qed_db_rec_sanity (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void qed_db_recovery_ring(struct qed_hwfn *p_hwfn,
				 struct qed_db_recovery_entry *db_entry)
{
	/* Print according to width */
	if (db_entry->db_width == DB_REC_WIDTH_32B) {
		DP_VERBOSE(p_hwfn, QED_MSG_SPQ,
			   "ringing doorbell address %p data %x\n",
			   db_entry->db_addr,
			   *(u32 *)db_entry->db_data);
	} else {
		DP_VERBOSE(p_hwfn, QED_MSG_SPQ,
			   "ringing doorbell address %p data %llx\n",
			   db_entry->db_addr,
			   *(u64 *)(db_entry->db_data));
	}

	/* Sanity */
	if (!qed_db_rec_sanity(p_hwfn->cdev, db_entry->db_addr,
			       db_entry->db_width, db_entry->db_data))
		return;

	/* Flush the write combined buffer. Since there are multiple doorbelling
	 * entities using the same address, if we don't flush, a transaction
	 * could be lost.
	 */
	wmb();

	/* Ring the doorbell */
	if (db_entry->db_width == DB_REC_WIDTH_32B)
		DIRECT_REG_WR(db_entry->db_addr,
			      *(u32 *)(db_entry->db_data));
	else
		DIRECT_REG_WR64(db_entry->db_addr,
				*(u64 *)(db_entry->db_data));

	/* Flush the write combined buffer. Next doorbell may come from a
	 * different entity to the same address...
	 */
	wmb();
}