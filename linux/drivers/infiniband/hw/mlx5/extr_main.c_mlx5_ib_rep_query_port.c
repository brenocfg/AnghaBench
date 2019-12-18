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
struct ib_port_attr {scalar_t__ gid_tbl_len; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int mlx5_query_port_roce (struct ib_device*,int /*<<< orphan*/ ,struct ib_port_attr*) ; 

__attribute__((used)) static int mlx5_ib_rep_query_port(struct ib_device *ibdev, u8 port,
				  struct ib_port_attr *props)
{
	int ret;

	/* Only link layer == ethernet is valid for representors
	 * and we always use port 1
	 */
	ret = mlx5_query_port_roce(ibdev, port, props);
	if (ret || !props)
		return ret;

	/* We don't support GIDS */
	props->gid_tbl_len = 0;

	return ret;
}