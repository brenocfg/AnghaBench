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

/* Variables and functions */
 int st33zp24_spi_read8_reg (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  st33zp24_status_to_errno (int) ; 

__attribute__((used)) static int st33zp24_spi_recv(void *phy_id, u8 tpm_register, u8 *tpm_data,
			     int tpm_size)
{
	int ret;

	ret = st33zp24_spi_read8_reg(phy_id, tpm_register, tpm_data, tpm_size);
	if (!st33zp24_status_to_errno(ret))
		return tpm_size;
	return ret;
}