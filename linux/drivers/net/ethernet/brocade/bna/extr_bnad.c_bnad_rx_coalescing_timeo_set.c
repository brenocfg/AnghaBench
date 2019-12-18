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
struct bnad_rx_info {int /*<<< orphan*/  rx; } ;
struct bnad {int num_rx; int /*<<< orphan*/  rx_coalescing_timeo; struct bnad_rx_info* rx_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  bna_rx_coalescing_timeo_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bnad_rx_coalescing_timeo_set(struct bnad *bnad)
{
	struct bnad_rx_info *rx_info;
	int	i;

	for (i = 0; i < bnad->num_rx; i++) {
		rx_info = &bnad->rx_info[i];
		if (!rx_info->rx)
			continue;
		bna_rx_coalescing_timeo_set(rx_info->rx,
				bnad->rx_coalescing_timeo);
	}
}