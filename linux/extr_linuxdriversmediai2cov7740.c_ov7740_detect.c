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
struct regmap {int dummy; } ;
struct ov7740 {struct regmap* regmap; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  REG_MIDH ; 
 int /*<<< orphan*/  REG_MIDL ; 
 int /*<<< orphan*/  REG_PIDH ; 
 int /*<<< orphan*/  REG_PIDL ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int ov7740_detect(struct ov7740 *ov7740)
{
	struct regmap *regmap = ov7740->regmap;
	unsigned int midh, midl, pidh, pidl;
	int ret;

	ret = regmap_read(regmap, REG_MIDH, &midh);
	if (ret)
		return ret;
	if (midh != 0x7f)
		return -ENODEV;

	ret = regmap_read(regmap, REG_MIDL, &midl);
	if (ret)
		return ret;
	if (midl != 0xa2)
		return -ENODEV;

	ret = regmap_read(regmap, REG_PIDH, &pidh);
	if (ret)
		return ret;
	if (pidh != 0x77)
		return -ENODEV;

	ret = regmap_read(regmap, REG_PIDL, &pidl);
	if (ret)
		return ret;
	if ((pidl != 0x40) && (pidl != 0x41) && (pidl != 0x42))
		return -ENODEV;

	return 0;
}