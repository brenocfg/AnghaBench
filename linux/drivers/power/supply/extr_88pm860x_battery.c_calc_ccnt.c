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
struct pm860x_battery_info {int dummy; } ;
struct ccnt {unsigned int pos; unsigned int neg; int spos; int total_chg; int total_dischg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCNT_NEG1 ; 
 int /*<<< orphan*/  CCNT_NEG2 ; 
 int /*<<< orphan*/  CCNT_POS1 ; 
 int /*<<< orphan*/  CCNT_POS2 ; 
 int /*<<< orphan*/  CCNT_SNEG ; 
 int /*<<< orphan*/  CCNT_SPOS ; 
 int read_ccnt (struct pm860x_battery_info*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int calc_ccnt(struct pm860x_battery_info *info, struct ccnt *ccnt)
{
	unsigned int sum;
	int ret;
	int data;

	ret = read_ccnt(info, CCNT_POS1, &data);
	if (ret)
		goto out;
	sum = data & 0xffff;
	ret = read_ccnt(info, CCNT_POS2, &data);
	if (ret)
		goto out;
	sum |= (data & 0xffff) << 16;
	ccnt->pos += sum;

	ret = read_ccnt(info, CCNT_NEG1, &data);
	if (ret)
		goto out;
	sum = data & 0xffff;
	ret = read_ccnt(info, CCNT_NEG2, &data);
	if (ret)
		goto out;
	sum |= (data & 0xffff) << 16;
	sum = ~sum + 1;		/* since it's negative */
	ccnt->neg += sum;

	ret = read_ccnt(info, CCNT_SPOS, &data);
	if (ret)
		goto out;
	ccnt->spos += data;
	ret = read_ccnt(info, CCNT_SNEG, &data);
	if (ret)
		goto out;

	/*
	 * charge(mAh)  = count * 1.6984 * 1e(-8)
	 *              = count * 16984 * 1.024 * 1.024 * 1.024 / (2 ^ 40)
	 *              = count * 18236 / (2 ^ 40)
	 */
	ccnt->total_chg = (int) ((ccnt->pos * 18236) >> 40);
	ccnt->total_dischg = (int) ((ccnt->neg * 18236) >> 40);
	return 0;
out:
	return ret;
}