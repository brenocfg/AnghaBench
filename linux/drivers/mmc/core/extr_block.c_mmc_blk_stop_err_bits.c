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
struct mmc_blk_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ERRORS ; 
 int /*<<< orphan*/  CMD_ERRORS_EXCL_OOR ; 
 scalar_t__ mmc_blk_oor_valid (struct mmc_blk_request*) ; 

__attribute__((used)) static inline u32 mmc_blk_stop_err_bits(struct mmc_blk_request *brq)
{
	return mmc_blk_oor_valid(brq) ? CMD_ERRORS : CMD_ERRORS_EXCL_OOR;
}