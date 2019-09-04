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

/* Variables and functions */
 int /*<<< orphan*/  LTR501_PS_DATA ; 
 int /*<<< orphan*/  LTR501_STATUS_PS_RDY ; 
 int ltr501_drdy (struct ltr501_data*,int /*<<< orphan*/ ) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int ltr501_read_ps(struct ltr501_data *data)
{
	int ret, status;

	ret = ltr501_drdy(data, LTR501_STATUS_PS_RDY);
	if (ret < 0)
		return ret;

	ret = regmap_bulk_read(data->regmap, LTR501_PS_DATA,
			       &status, 2);
	if (ret < 0)
		return ret;

	return status;
}