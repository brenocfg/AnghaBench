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
typedef  int u64 ;
struct SPU2_FMD {int /*<<< orphan*/  ctrl3; } ;

/* Variables and functions */
 int SPU2_PL_LEN ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 

__attribute__((used)) static void spu2_fmd_ctrl3_write(struct SPU2_FMD *fmd, u64 payload_len)
{
	u64 ctrl3;

	ctrl3 = payload_len & SPU2_PL_LEN;

	fmd->ctrl3 = cpu_to_le64(ctrl3);
}