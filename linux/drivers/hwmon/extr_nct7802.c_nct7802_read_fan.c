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
typedef  int /*<<< orphan*/  u8 ;
struct nct7802_data {int /*<<< orphan*/  access_lock; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (unsigned int,int) ; 
 int /*<<< orphan*/  REG_FANCOUNT_LOW ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int nct7802_read_fan(struct nct7802_data *data, u8 reg_fan)
{
	unsigned int f1, f2;
	int ret;

	mutex_lock(&data->access_lock);
	ret = regmap_read(data->regmap, reg_fan, &f1);
	if (ret < 0)
		goto abort;
	ret = regmap_read(data->regmap, REG_FANCOUNT_LOW, &f2);
	if (ret < 0)
		goto abort;
	ret = (f1 << 5) | (f2 >> 3);
	/* convert fan count to rpm */
	if (ret == 0x1fff)	/* maximum value, assume fan is stopped */
		ret = 0;
	else if (ret)
		ret = DIV_ROUND_CLOSEST(1350000U, ret);
abort:
	mutex_unlock(&data->access_lock);
	return ret;
}