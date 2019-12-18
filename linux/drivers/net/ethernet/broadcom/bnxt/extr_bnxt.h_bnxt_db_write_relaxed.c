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
struct bnxt_db_info {int db_key64; int db_key32; int /*<<< orphan*/  doorbell; } ;
struct bnxt {int flags; } ;

/* Variables and functions */
 int BNXT_FLAG_CHIP_P5 ; 
 int BNXT_FLAG_DOUBLE_DB ; 
 int /*<<< orphan*/  writel_relaxed (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeq_relaxed (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void bnxt_db_write_relaxed(struct bnxt *bp,
					 struct bnxt_db_info *db, u32 idx)
{
	if (bp->flags & BNXT_FLAG_CHIP_P5) {
		writeq_relaxed(db->db_key64 | idx, db->doorbell);
	} else {
		u32 db_val = db->db_key32 | idx;

		writel_relaxed(db_val, db->doorbell);
		if (bp->flags & BNXT_FLAG_DOUBLE_DB)
			writel_relaxed(db_val, db->doorbell);
	}
}