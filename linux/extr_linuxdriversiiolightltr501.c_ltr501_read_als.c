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
struct ltr501_data {int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  LTR501_ALS_DATA1 ; 
 int /*<<< orphan*/  LTR501_STATUS_ALS_RDY ; 
 int ltr501_drdy (struct ltr501_data*,int /*<<< orphan*/ ) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ltr501_read_als(struct ltr501_data *data, __le16 buf[2])
{
	int ret;

	ret = ltr501_drdy(data, LTR501_STATUS_ALS_RDY);
	if (ret < 0)
		return ret;
	/* always read both ALS channels in given order */
	return regmap_bulk_read(data->regmap, LTR501_ALS_DATA1,
				buf, 2 * sizeof(__le16));
}