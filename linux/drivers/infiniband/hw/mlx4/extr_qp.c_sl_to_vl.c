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
union sl2vl_tbl_to_u64 {int* sl8; int /*<<< orphan*/  sl64; } ;
typedef  int u8 ;
struct mlx4_ib_dev {int /*<<< orphan*/ * sl2vl; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 sl_to_vl(struct mlx4_ib_dev *dev, u8 sl, int port_num)
{
	union sl2vl_tbl_to_u64 tmp_vltab;
	u8 vl;

	if (sl > 15)
		return 0xf;
	tmp_vltab.sl64 = atomic64_read(&dev->sl2vl[port_num - 1]);
	vl = tmp_vltab.sl8[sl >> 1];
	if (sl & 1)
		vl &= 0x0f;
	else
		vl >>= 4;
	return vl;
}