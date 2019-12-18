#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlx5e_channels {int num; TYPE_1__** c; } ;
struct TYPE_2__ {int /*<<< orphan*/  rq; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int MLX5E_RQ_WQES_TIMEOUT ; 
 int mlx5e_wait_for_min_rx_wqes (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mlx5e_wait_channels_min_rx_wqes(struct mlx5e_channels *chs)
{
	int err = 0;
	int i;

	for (i = 0; i < chs->num; i++) {
		int timeout = err ? 0 : MLX5E_RQ_WQES_TIMEOUT;

		err |= mlx5e_wait_for_min_rx_wqes(&chs->c[i]->rq, timeout);

		/* Don't wait on the XSK RQ, because the newer xdpsock sample
		 * doesn't provide any Fill Ring entries at the setup stage.
		 */
	}

	return err ? -ETIMEDOUT : 0;
}