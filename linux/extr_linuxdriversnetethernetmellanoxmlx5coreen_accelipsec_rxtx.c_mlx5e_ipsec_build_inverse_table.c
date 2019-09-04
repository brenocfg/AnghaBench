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
typedef  size_t u32 ;
typedef  int u16 ;

/* Variables and functions */
 size_t MAX_LSO_MSS ; 
 int div_u64 (unsigned long long,size_t) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/ * mlx5e_ipsec_inverse_table ; 

void mlx5e_ipsec_build_inverse_table(void)
{
	u16 mss_inv;
	u32 mss;

	/* Calculate 1/x inverse table for use in GSO data path.
	 * Using this table, we provide the IPSec accelerator with the value of
	 * 1/gso_size so that it can infer the position of each segment inside
	 * the GSO, and increment the ESP sequence number, and generate the IV.
	 * The HW needs this value in Q0.16 fixed-point number format
	 */
	mlx5e_ipsec_inverse_table[1] = htons(0xFFFF);
	for (mss = 2; mss < MAX_LSO_MSS; mss++) {
		mss_inv = div_u64(1ULL << 32, mss) >> 16;
		mlx5e_ipsec_inverse_table[mss] = htons(mss_inv);
	}
}