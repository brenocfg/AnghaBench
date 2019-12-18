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
struct bnxt_qplib_chip_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RING_ALLOC_REQ_RING_TYPE_NQ ; 
 int /*<<< orphan*/  RING_ALLOC_REQ_RING_TYPE_ROCE_CMPL ; 
 scalar_t__ bnxt_qplib_is_chip_gen_p5 (struct bnxt_qplib_chip_ctx*) ; 

__attribute__((used)) static inline u8 bnxt_qplib_get_ring_type(struct bnxt_qplib_chip_ctx *cctx)
{
	return bnxt_qplib_is_chip_gen_p5(cctx) ?
	       RING_ALLOC_REQ_RING_TYPE_NQ :
	       RING_ALLOC_REQ_RING_TYPE_ROCE_CMPL;
}