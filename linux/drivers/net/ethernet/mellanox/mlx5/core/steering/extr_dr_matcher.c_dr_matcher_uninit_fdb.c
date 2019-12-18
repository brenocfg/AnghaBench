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
struct mlx5dr_matcher {int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  dr_matcher_uninit_nic (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dr_matcher_uninit_fdb(struct mlx5dr_matcher *matcher)
{
	dr_matcher_uninit_nic(&matcher->rx);
	dr_matcher_uninit_nic(&matcher->tx);
}