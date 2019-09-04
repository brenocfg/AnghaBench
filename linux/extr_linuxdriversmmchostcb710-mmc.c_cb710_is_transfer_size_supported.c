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
struct mmc_data {int blksz; int blocks; } ;

/* Variables and functions */

__attribute__((used)) static bool cb710_is_transfer_size_supported(struct mmc_data *data)
{
	return !(data->blksz & 15 && (data->blocks != 1 || data->blksz != 8));
}