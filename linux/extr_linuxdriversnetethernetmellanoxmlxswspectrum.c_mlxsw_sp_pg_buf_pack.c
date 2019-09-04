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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_reg_pbmc_lossless_buffer_pack (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_pbmc_lossy_buffer_pack (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp_pg_buf_pack(char *pbmc_pl, int index, u16 size, u16 thres,
				 bool lossy)
{
	if (lossy)
		mlxsw_reg_pbmc_lossy_buffer_pack(pbmc_pl, index, size);
	else
		mlxsw_reg_pbmc_lossless_buffer_pack(pbmc_pl, index, size,
						    thres);
}