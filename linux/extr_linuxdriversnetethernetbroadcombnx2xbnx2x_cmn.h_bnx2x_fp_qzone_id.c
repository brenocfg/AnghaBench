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
typedef  scalar_t__ u8 ;
struct bnx2x_fastpath {scalar_t__ cl_id; int /*<<< orphan*/  bp; } ;

/* Variables and functions */
 int BP_PORT (int /*<<< orphan*/ ) ; 
 scalar_t__ CHIP_IS_E1x (int /*<<< orphan*/ ) ; 
 int ETH_MAX_RX_CLIENTS_E1H ; 

__attribute__((used)) static inline u8 bnx2x_fp_qzone_id(struct bnx2x_fastpath *fp)
{
	if (CHIP_IS_E1x(fp->bp))
		return fp->cl_id + BP_PORT(fp->bp) * ETH_MAX_RX_CLIENTS_E1H;
	else
		return fp->cl_id;
}