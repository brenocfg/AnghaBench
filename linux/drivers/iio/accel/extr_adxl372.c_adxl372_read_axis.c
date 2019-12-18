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
struct adxl372_state {int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  regval ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int adxl372_read_axis(struct adxl372_state *st, u8 addr)
{
	__be16 regval;
	int ret;

	ret = regmap_bulk_read(st->regmap, addr, &regval, sizeof(regval));
	if (ret < 0)
		return ret;

	return be16_to_cpu(regval);
}