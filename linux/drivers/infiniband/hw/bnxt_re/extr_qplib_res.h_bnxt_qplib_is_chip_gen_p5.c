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
struct bnxt_qplib_chip_ctx {scalar_t__ chip_num; } ;

/* Variables and functions */
 scalar_t__ CHIP_NUM_57500 ; 

__attribute__((used)) static inline bool bnxt_qplib_is_chip_gen_p5(struct bnxt_qplib_chip_ctx *cctx)
{
	return (cctx->chip_num == CHIP_NUM_57500);
}