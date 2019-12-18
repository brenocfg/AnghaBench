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
struct mlx5dr_matcher {int /*<<< orphan*/  rx; int /*<<< orphan*/  tx; } ;

/* Variables and functions */
 int dr_matcher_init_nic (struct mlx5dr_matcher*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dr_matcher_uninit_nic (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dr_matcher_init_fdb(struct mlx5dr_matcher *matcher)
{
	int ret;

	ret = dr_matcher_init_nic(matcher, &matcher->rx);
	if (ret)
		return ret;

	ret = dr_matcher_init_nic(matcher, &matcher->tx);
	if (ret)
		goto uninit_nic_rx;

	return 0;

uninit_nic_rx:
	dr_matcher_uninit_nic(&matcher->rx);
	return ret;
}