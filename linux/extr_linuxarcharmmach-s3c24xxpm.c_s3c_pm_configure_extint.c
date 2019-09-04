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
 int S3C2410_GPF (int) ; 
 int S3C2410_GPG (int) ; 
 int /*<<< orphan*/  s3c_pm_check_resume_pin (int,int) ; 

void s3c_pm_configure_extint(void)
{
	int pin;

	/* for each of the external interrupts (EINT0..EINT15) we
	 * need to check whether it is an external interrupt source,
	 * and then configure it as an input if it is not
	*/

	for (pin = S3C2410_GPF(0); pin <= S3C2410_GPF(7); pin++) {
		s3c_pm_check_resume_pin(pin, pin - S3C2410_GPF(0));
	}

	for (pin = S3C2410_GPG(0); pin <= S3C2410_GPG(7); pin++) {
		s3c_pm_check_resume_pin(pin, (pin - S3C2410_GPG(0))+8);
	}
}