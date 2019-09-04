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
struct max30102_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX30102_REG_INT_STATUS ; 
 unsigned int MAX30102_REG_INT_STATUS_FIFO_RDY ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static inline int max30102_fifo_count(struct max30102_data *data)
{
	unsigned int val;
	int ret;

	ret = regmap_read(data->regmap, MAX30102_REG_INT_STATUS, &val);
	if (ret)
		return ret;

	/* FIFO has one sample slot left */
	if (val & MAX30102_REG_INT_STATUS_FIFO_RDY)
		return 1;

	return 0;
}