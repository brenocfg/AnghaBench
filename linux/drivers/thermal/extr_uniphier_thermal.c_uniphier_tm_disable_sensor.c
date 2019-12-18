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
struct uniphier_tm_dev {TYPE_1__* data; struct regmap* regmap; } ;
struct regmap {int dummy; } ;
struct TYPE_2__ {scalar_t__ block_base; scalar_t__ map_base; } ;

/* Variables and functions */
 scalar_t__ PMALERTINTCTL ; 
 int /*<<< orphan*/  PMALERTINTCTL_MASK ; 
 scalar_t__ PVTCTLEN ; 
 int /*<<< orphan*/  PVTCTLEN_EN ; 
 int /*<<< orphan*/  regmap_write_bits (struct regmap*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void uniphier_tm_disable_sensor(struct uniphier_tm_dev *tdev)
{
	struct regmap *map = tdev->regmap;

	/* disable alert interrupt */
	regmap_write_bits(map, tdev->data->map_base + PMALERTINTCTL,
			  PMALERTINTCTL_MASK, 0);

	/* stop PVT */
	regmap_write_bits(map, tdev->data->block_base + PVTCTLEN,
			  PVTCTLEN_EN, 0);

	usleep_range(1000, 2000);	/* The spec note says at least 1ms */
}