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
typedef  int u8 ;
struct tps80031_pupd_init_data {size_t input_pin; scalar_t__ setting; } ;
struct tps80031_pupd_data {int pulldown_bit; int pullup_bit; int /*<<< orphan*/  reg; } ;
struct tps80031_platform_data {int pupd_init_data_size; struct tps80031_pupd_init_data* pupd_init_data; } ;
struct tps80031 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ TPS80031_PUPD_PULLDOWN ; 
 scalar_t__ TPS80031_PUPD_PULLUP ; 
 int /*<<< orphan*/  TPS80031_SLAVE_ID1 ; 
 struct tps80031_pupd_data* tps80031_pupds ; 
 int /*<<< orphan*/  tps80031_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void tps80031_pupd_init(struct tps80031 *tps80031,
			       struct tps80031_platform_data *pdata)
{
	struct tps80031_pupd_init_data *pupd_init_data = pdata->pupd_init_data;
	int data_size = pdata->pupd_init_data_size;
	int i;

	for (i = 0; i < data_size; ++i) {
		struct tps80031_pupd_init_data *pupd_init = &pupd_init_data[i];
		const struct tps80031_pupd_data *pupd =
			&tps80031_pupds[pupd_init->input_pin];
		u8 update_value = 0;
		u8 update_mask = pupd->pulldown_bit | pupd->pullup_bit;

		if (pupd_init->setting == TPS80031_PUPD_PULLDOWN)
			update_value = pupd->pulldown_bit;
		else if (pupd_init->setting == TPS80031_PUPD_PULLUP)
			update_value = pupd->pullup_bit;

		tps80031_update(tps80031->dev, TPS80031_SLAVE_ID1, pupd->reg,
				update_value, update_mask);
	}
}