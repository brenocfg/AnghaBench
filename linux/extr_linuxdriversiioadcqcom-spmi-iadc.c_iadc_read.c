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
typedef  unsigned int u8 ;
typedef  scalar_t__ u16 ;
struct iadc_chip {scalar_t__ base; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,unsigned int*) ; 

__attribute__((used)) static int iadc_read(struct iadc_chip *iadc, u16 offset, u8 *data)
{
	unsigned int val;
	int ret;

	ret = regmap_read(iadc->regmap, iadc->base + offset, &val);
	if (ret < 0)
		return ret;

	*data = val;
	return 0;
}