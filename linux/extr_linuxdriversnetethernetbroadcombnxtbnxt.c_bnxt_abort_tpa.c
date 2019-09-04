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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct bnxt_napi {int dummy; } ;
struct bnxt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_reuse_rx_agg_bufs (struct bnxt_napi*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void bnxt_abort_tpa(struct bnxt *bp, struct bnxt_napi *bnapi,
			   u16 cp_cons, u32 agg_bufs)
{
	if (agg_bufs)
		bnxt_reuse_rx_agg_bufs(bnapi, cp_cons, agg_bufs);
}