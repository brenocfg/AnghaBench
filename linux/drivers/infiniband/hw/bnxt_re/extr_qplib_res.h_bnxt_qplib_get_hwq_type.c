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
typedef  int /*<<< orphan*/  u8 ;
struct bnxt_qplib_res {int /*<<< orphan*/  cctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  HWQ_TYPE_L2_CMPL ; 
 int /*<<< orphan*/  HWQ_TYPE_QUEUE ; 
 scalar_t__ bnxt_qplib_is_chip_gen_p5 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 bnxt_qplib_get_hwq_type(struct bnxt_qplib_res *res)
{
	return bnxt_qplib_is_chip_gen_p5(res->cctx) ?
					HWQ_TYPE_QUEUE : HWQ_TYPE_L2_CMPL;
}