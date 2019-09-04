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
struct hwtstamp_config {scalar_t__ rx_filter; } ;

/* Variables and functions */
 scalar_t__ HWTSTAMP_FILTER_ALL ; 

__attribute__((used)) static inline bool mlx5e_rx_hw_stamp(struct hwtstamp_config *config)
{
	return config->rx_filter == HWTSTAMP_FILTER_ALL;
}