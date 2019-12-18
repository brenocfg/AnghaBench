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
typedef  int u8 ;
typedef  int u16 ;
struct mlxsw_sp_acl_erp_delta {int start; int mask; } ;

/* Variables and functions */
 size_t __MASK_IDX (int) ; 
 int __MASK_LEN ; 

void mlxsw_sp_acl_erp_delta_clear(const struct mlxsw_sp_acl_erp_delta *delta,
				  const char *enc_key)
{
	u16 start = delta->start;
	u8 mask = delta->mask;
	unsigned char *byte;
	u16 tmp;

	tmp = mask;
	tmp <<= start % 8;
	tmp = ~tmp;

	byte = (unsigned char *) &enc_key[__MASK_IDX(start / 8)];
	*byte &= tmp & 0xff;
	if (start / 8 + 1 < __MASK_LEN) {
		byte = (unsigned char *) &enc_key[__MASK_IDX(start / 8 + 1)];
		*byte &= (tmp >> 8) & 0xff;
	}
}