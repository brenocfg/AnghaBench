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
struct adxl372_state {unsigned int watermark; unsigned int fifo_set_size; int /*<<< orphan*/  regmap; int /*<<< orphan*/  fifo_mode; int /*<<< orphan*/  fifo_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADXL372_FIFO_CTL ; 
 unsigned int ADXL372_FIFO_CTL_FORMAT_MODE (int /*<<< orphan*/ ) ; 
 unsigned int ADXL372_FIFO_CTL_MODE_MODE (int /*<<< orphan*/ ) ; 
 unsigned int ADXL372_FIFO_CTL_SAMPLES_MODE (unsigned int) ; 
 int /*<<< orphan*/  ADXL372_FIFO_SAMPLES ; 
 int /*<<< orphan*/  ADXL372_FULL_BW_MEASUREMENT ; 
 int /*<<< orphan*/  ADXL372_STANDBY ; 
 int adxl372_set_op_mode (struct adxl372_state*,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int adxl372_configure_fifo(struct adxl372_state *st)
{
	unsigned int fifo_samples, fifo_ctl;
	int ret;

	/* FIFO must be configured while in standby mode */
	ret = adxl372_set_op_mode(st, ADXL372_STANDBY);
	if (ret < 0)
		return ret;

	/*
	 * watermark stores the number of sets; we need to write the FIFO
	 * registers with the number of samples
	 */
	fifo_samples = (st->watermark * st->fifo_set_size);
	fifo_ctl = ADXL372_FIFO_CTL_FORMAT_MODE(st->fifo_format) |
		   ADXL372_FIFO_CTL_MODE_MODE(st->fifo_mode) |
		   ADXL372_FIFO_CTL_SAMPLES_MODE(fifo_samples);

	ret = regmap_write(st->regmap,
			   ADXL372_FIFO_SAMPLES, fifo_samples & 0xFF);
	if (ret < 0)
		return ret;

	ret = regmap_write(st->regmap, ADXL372_FIFO_CTL, fifo_ctl);
	if (ret < 0)
		return ret;

	return adxl372_set_op_mode(st, ADXL372_FULL_BW_MEASUREMENT);
}