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
typedef  int /*<<< orphan*/  u32 ;
struct bnxt_db_info {int dummy; } ;
struct bnxt {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_DB_CQ (struct bnxt_db_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNXT_DB_NQ_P5 (struct bnxt_db_info*,int /*<<< orphan*/ ) ; 
 int BNXT_FLAG_CHIP_P5 ; 

__attribute__((used)) static void bnxt_db_nq(struct bnxt *bp, struct bnxt_db_info *db, u32 idx)
{
	if (bp->flags & BNXT_FLAG_CHIP_P5)
		BNXT_DB_NQ_P5(db, idx);
	else
		BNXT_DB_CQ(db, idx);
}