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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct tpm_tis_data {int dummy; } ;

/* Variables and functions */
 int tpm_tis_spi_transfer (struct tpm_tis_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int tpm_tis_spi_write_bytes(struct tpm_tis_data *data, u32 addr,
				   u16 len, const u8 *value)
{
	return tpm_tis_spi_transfer(data, addr, len, NULL, value);
}