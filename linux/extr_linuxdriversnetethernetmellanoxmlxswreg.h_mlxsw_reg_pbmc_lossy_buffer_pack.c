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
 int /*<<< orphan*/  mlxsw_reg_pbmc_buf_epsb_set (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_pbmc_buf_lossy_set (char*,int,int) ; 
 int /*<<< orphan*/  mlxsw_reg_pbmc_buf_size_set (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlxsw_reg_pbmc_lossy_buffer_pack(char *payload,
						    int buf_index,
						    u16 size)
{
	mlxsw_reg_pbmc_buf_lossy_set(payload, buf_index, 1);
	mlxsw_reg_pbmc_buf_epsb_set(payload, buf_index, 0);
	mlxsw_reg_pbmc_buf_size_set(payload, buf_index, size);
}