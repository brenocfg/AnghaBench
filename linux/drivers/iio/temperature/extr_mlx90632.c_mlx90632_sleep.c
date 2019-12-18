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
struct mlx90632_data {int /*<<< orphan*/  regmap; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int mlx90632_pwr_set_sleep_step (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_mark_dirty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx90632_sleep(struct mlx90632_data *data)
{
	regcache_mark_dirty(data->regmap);

	dev_dbg(&data->client->dev, "Requesting sleep");
	return mlx90632_pwr_set_sleep_step(data->regmap);
}