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
 int EBUSY ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  KERNCZ_IMC_IDX ; 
 int MAX_TIMEOUT ; 
 int piix4_imc_read (int) ; 
 int /*<<< orphan*/  piix4_imc_write (int,int) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  request_muxed_region (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int piix4_imc_sleep(void)
{
	int timeout = MAX_TIMEOUT;

	if (!request_muxed_region(KERNCZ_IMC_IDX, 2, "smbus_kerncz_imc"))
		return -EBUSY;

	/* clear response register */
	piix4_imc_write(0x82, 0x00);
	/* request ownership flag */
	piix4_imc_write(0x83, 0xB4);
	/* kick off IMC Mailbox command 96 */
	piix4_imc_write(0x80, 0x96);

	while (timeout--) {
		if (piix4_imc_read(0x82) == 0xfa) {
			release_region(KERNCZ_IMC_IDX, 2);
			return 0;
		}
		usleep_range(1000, 2000);
	}

	release_region(KERNCZ_IMC_IDX, 2);
	return -ETIMEDOUT;
}