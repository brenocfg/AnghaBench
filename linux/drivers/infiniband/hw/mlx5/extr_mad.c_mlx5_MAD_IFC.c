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
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct ib_wc {int dummy; } ;
struct ib_mad {int dummy; } ;
struct ib_grh {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  can_do_mad_ifc (struct mlx5_ib_dev*,int,struct ib_mad*) ; 
 int mlx5_cmd_mad_ifc (int /*<<< orphan*/ ,void const*,void*,int,int) ; 

__attribute__((used)) static int mlx5_MAD_IFC(struct mlx5_ib_dev *dev, int ignore_mkey,
			int ignore_bkey, u8 port, const struct ib_wc *in_wc,
			const struct ib_grh *in_grh, const void *in_mad,
			void *response_mad)
{
	u8 op_modifier = 0;

	if (!can_do_mad_ifc(dev, port, (struct ib_mad *)in_mad))
		return -EPERM;

	/* Key check traps can't be generated unless we have in_wc to
	 * tell us where to send the trap.
	 */
	if (ignore_mkey || !in_wc)
		op_modifier |= 0x1;
	if (ignore_bkey || !in_wc)
		op_modifier |= 0x2;

	return mlx5_cmd_mad_ifc(dev->mdev, in_mad, response_mad, op_modifier,
				port);
}