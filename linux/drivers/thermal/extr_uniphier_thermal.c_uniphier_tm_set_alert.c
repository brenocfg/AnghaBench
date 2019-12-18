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
typedef  int u32 ;
struct uniphier_tm_dev {TYPE_1__* data; struct regmap* regmap; } ;
struct regmap {int dummy; } ;
struct TYPE_2__ {scalar_t__ map_base; } ;

/* Variables and functions */
 scalar_t__ SETALERT0 ; 
 int SETALERT_EN ; 
 int SETALERT_TEMP_OVF ; 
 int SETALERT_TEMP_OVF_VALUE (int) ; 
 int /*<<< orphan*/  regmap_write_bits (struct regmap*,scalar_t__,int,int) ; 

__attribute__((used)) static void uniphier_tm_set_alert(struct uniphier_tm_dev *tdev, u32 ch,
				  u32 temp)
{
	struct regmap *map = tdev->regmap;

	/* set alert temperature */
	regmap_write_bits(map, tdev->data->map_base + SETALERT0 + (ch << 2),
			  SETALERT_EN | SETALERT_TEMP_OVF,
			  SETALERT_EN |
			  SETALERT_TEMP_OVF_VALUE(temp / 1000));
}