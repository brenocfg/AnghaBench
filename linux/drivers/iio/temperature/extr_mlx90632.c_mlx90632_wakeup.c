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
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int mlx90632_pwr_continuous (int /*<<< orphan*/ ) ; 
 int regcache_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx90632_wakeup(struct mlx90632_data *data)
{
	int ret;

	ret = regcache_sync(data->regmap);
	if (ret < 0) {
		dev_err(&data->client->dev,
			"Failed to sync regmap registers: %d\n", ret);
		return ret;
	}

	dev_dbg(&data->client->dev, "Requesting wake-up\n");
	return mlx90632_pwr_continuous(data->regmap);
}