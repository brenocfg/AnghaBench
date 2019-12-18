#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sih {unsigned int irq_lines; int /*<<< orphan*/  bytes_ixr; TYPE_1__* mask; int /*<<< orphan*/  module; scalar_t__ set_cor; int /*<<< orphan*/  name; int /*<<< orphan*/  control_offset; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  isr_offset; int /*<<< orphan*/  imr_offset; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TWL4030_SIH_CTRL_COR_MASK ; 
 unsigned int irq_line ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int nr_sih_modules ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_warn (char*,int,...) ; 
 struct sih* sih_modules ; 
 int twl_i2c_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int twl_i2c_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int twl_i2c_write_u8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_init_sih_modules(unsigned line)
{
	const struct sih *sih;
	u8 buf[4];
	int i;
	int status;

	/* line 0 == int1_n signal; line 1 == int2_n signal */
	if (line > 1)
		return -EINVAL;

	irq_line = line;

	/* disable all interrupts on our line */
	memset(buf, 0xff, sizeof(buf));
	sih = sih_modules;
	for (i = 0; i < nr_sih_modules; i++, sih++) {
		/* skip USB -- it's funky */
		if (!sih->bytes_ixr)
			continue;

		/* Not all the SIH modules support multiple interrupt lines */
		if (sih->irq_lines <= line)
			continue;

		status = twl_i2c_write(sih->module, buf,
				sih->mask[line].imr_offset, sih->bytes_ixr);
		if (status < 0)
			pr_err("twl4030: err %d initializing %s %s\n",
					status, sih->name, "IMR");

		/*
		 * Maybe disable "exclusive" mode; buffer second pending irq;
		 * set Clear-On-Read (COR) bit.
		 *
		 * NOTE that sometimes COR polarity is documented as being
		 * inverted:  for MADC, COR=1 means "clear on write".
		 * And for PWR_INT it's not documented...
		 */
		if (sih->set_cor) {
			status = twl_i2c_write_u8(sih->module,
					TWL4030_SIH_CTRL_COR_MASK,
					sih->control_offset);
			if (status < 0)
				pr_err("twl4030: err %d initializing %s %s\n",
						status, sih->name, "SIH_CTRL");
		}
	}

	sih = sih_modules;
	for (i = 0; i < nr_sih_modules; i++, sih++) {
		u8 rxbuf[4];
		int j;

		/* skip USB */
		if (!sih->bytes_ixr)
			continue;

		/* Not all the SIH modules support multiple interrupt lines */
		if (sih->irq_lines <= line)
			continue;

		/*
		 * Clear pending interrupt status.  Either the read was
		 * enough, or we need to write those bits.  Repeat, in
		 * case an IRQ is pending (PENDDIS=0) ... that's not
		 * uncommon with PWR_INT.PWRON.
		 */
		for (j = 0; j < 2; j++) {
			status = twl_i2c_read(sih->module, rxbuf,
				sih->mask[line].isr_offset, sih->bytes_ixr);
			if (status < 0)
				pr_warn("twl4030: err %d initializing %s %s\n",
					status, sih->name, "ISR");

			if (!sih->set_cor) {
				status = twl_i2c_write(sih->module, buf,
					sih->mask[line].isr_offset,
					sih->bytes_ixr);
				if (status < 0)
					pr_warn("twl4030: write failed: %d\n",
						status);
			}
			/*
			 * else COR=1 means read sufficed.
			 * (for most SIH modules...)
			 */
		}
	}

	return 0;
}