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
struct adxl372_state {int bw; int /*<<< orphan*/  regmap; } ;
typedef  enum adxl372_bandwidth { ____Placeholder_adxl372_bandwidth } adxl372_bandwidth ;

/* Variables and functions */
 int /*<<< orphan*/  ADXL372_MEASURE ; 
 int /*<<< orphan*/  ADXL372_MEASURE_BANDWIDTH_MODE (int) ; 
 int /*<<< orphan*/  ADXL372_MEASURE_BANDWIDTH_MSK ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adxl372_set_bandwidth(struct adxl372_state *st,
				 enum adxl372_bandwidth bw)
{
	int ret;

	ret = regmap_update_bits(st->regmap, ADXL372_MEASURE,
				 ADXL372_MEASURE_BANDWIDTH_MSK,
				 ADXL372_MEASURE_BANDWIDTH_MODE(bw));
	if (ret < 0)
		return ret;

	st->bw = bw;

	return ret;
}