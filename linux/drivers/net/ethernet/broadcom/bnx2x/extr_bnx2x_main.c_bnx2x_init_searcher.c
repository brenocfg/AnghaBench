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
struct bnx2x {int /*<<< orphan*/  t2_mapping; int /*<<< orphan*/  t2; } ;

/* Variables and functions */
 int BP_PORT (struct bnx2x*) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRC_CONN_NUM ; 
 int /*<<< orphan*/  SRC_HASH_BITS ; 
 scalar_t__ SRC_REG_NUMBER_HASH_BITS0 ; 
 int /*<<< orphan*/  bnx2x_src_init_t2 (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_init_searcher(struct bnx2x *bp)
{
	int port = BP_PORT(bp);
	bnx2x_src_init_t2(bp, bp->t2, bp->t2_mapping, SRC_CONN_NUM);
	/* T1 hash bits value determines the T1 number of entries */
	REG_WR(bp, SRC_REG_NUMBER_HASH_BITS0 + port*4, SRC_HASH_BITS);
}