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

/* Variables and functions */
 int /*<<< orphan*/  GPIOF_OUT_INIT_HIGH ; 
 int /*<<< orphan*/  H1940_SUSPEND_CHECK ; 
 int /*<<< orphan*/  H1940_SUSPEND_CHECKSUM ; 
 int /*<<< orphan*/  S3C2410_GPF (int) ; 
 int /*<<< orphan*/  S3C2410_GPG (int) ; 
 int /*<<< orphan*/  S3C2410_GPIO_INPUT ; 
 void* S3C2410_GSTATUS3 ; 
 void* S3C2410_GSTATUS4 ; 
 int /*<<< orphan*/  S3C_PMDBG (char*,scalar_t__) ; 
 unsigned long __pa_symbol (int /*<<< orphan*/ ) ; 
 scalar_t__ __raw_readl (void*) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,void*) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_request_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ machine_is_aml_m5900 () ; 
 scalar_t__ machine_is_h1940 () ; 
 scalar_t__ machine_is_rx1950 () ; 
 scalar_t__ machine_is_rx3715 () ; 
 void* phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_cpu_resume ; 
 int /*<<< orphan*/  s3c_gpio_cfgpin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s3c2410_pm_prepare(void)
{
	/* ensure at least GSTATUS3 has the resume address */

	__raw_writel(__pa_symbol(s3c_cpu_resume), S3C2410_GSTATUS3);

	S3C_PMDBG("GSTATUS3 0x%08x\n", __raw_readl(S3C2410_GSTATUS3));
	S3C_PMDBG("GSTATUS4 0x%08x\n", __raw_readl(S3C2410_GSTATUS4));

	if (machine_is_h1940()) {
		void *base = phys_to_virt(H1940_SUSPEND_CHECK);
		unsigned long ptr;
		unsigned long calc = 0;

		/* generate check for the bootloader to check on resume */

		for (ptr = 0; ptr < 0x40000; ptr += 0x400)
			calc += __raw_readl(base+ptr);

		__raw_writel(calc, phys_to_virt(H1940_SUSPEND_CHECKSUM));
	}

	/* RX3715 and RX1950 use similar to H1940 code and the
	 * same offsets for resume and checksum pointers */

	if (machine_is_rx3715() || machine_is_rx1950()) {
		void *base = phys_to_virt(H1940_SUSPEND_CHECK);
		unsigned long ptr;
		unsigned long calc = 0;

		/* generate check for the bootloader to check on resume */

		for (ptr = 0; ptr < 0x40000; ptr += 0x4)
			calc += __raw_readl(base+ptr);

		__raw_writel(calc, phys_to_virt(H1940_SUSPEND_CHECKSUM));
	}

	if (machine_is_aml_m5900()) {
		gpio_request_one(S3C2410_GPF(2), GPIOF_OUT_INIT_HIGH, NULL);
		gpio_free(S3C2410_GPF(2));
	}

	if (machine_is_rx1950()) {
		/* According to S3C2442 user's manual, page 7-17,
		 * when the system is operating in NAND boot mode,
		 * the hardware pin configuration - EINT[23:21] –
		 * must be set as input for starting up after
		 * wakeup from sleep mode
		 */
		s3c_gpio_cfgpin(S3C2410_GPG(13), S3C2410_GPIO_INPUT);
		s3c_gpio_cfgpin(S3C2410_GPG(14), S3C2410_GPIO_INPUT);
		s3c_gpio_cfgpin(S3C2410_GPG(15), S3C2410_GPIO_INPUT);
	}
}