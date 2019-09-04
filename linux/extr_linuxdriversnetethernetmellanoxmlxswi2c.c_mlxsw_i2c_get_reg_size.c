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
typedef  int u16 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int MLXSW_I2C_TLV_HDR_SIZE ; 
 int be16_to_cpup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int mlxsw_i2c_get_reg_size(u8 *in_mbox)
{
	u16  tmp = be16_to_cpup((__be16 *) (in_mbox + MLXSW_I2C_TLV_HDR_SIZE));

	return (tmp & 0x7ff) * 4 + MLXSW_I2C_TLV_HDR_SIZE;
}