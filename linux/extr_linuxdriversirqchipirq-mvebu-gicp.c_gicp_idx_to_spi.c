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
struct mvebu_gicp_spi_range {int count; int start; } ;
struct mvebu_gicp {int spi_ranges_cnt; struct mvebu_gicp_spi_range* spi_ranges; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int gicp_idx_to_spi(struct mvebu_gicp *gicp, int idx)
{
	int i;

	for (i = 0; i < gicp->spi_ranges_cnt; i++) {
		struct mvebu_gicp_spi_range *r = &gicp->spi_ranges[i];

		if (idx < r->count)
			return r->start + idx;

		idx -= r->count;
	}

	return -EINVAL;
}