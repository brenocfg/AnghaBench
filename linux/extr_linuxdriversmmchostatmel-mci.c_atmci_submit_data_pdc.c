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
struct mmc_data {int flags; } ;
struct atmel_mci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_PDC_PTCR ; 
 int /*<<< orphan*/  ATMEL_PDC_RXTEN ; 
 int /*<<< orphan*/  ATMEL_PDC_TXTEN ; 
 int MMC_DATA_READ ; 
 int /*<<< orphan*/  atmci_writel (struct atmel_mci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
atmci_submit_data_pdc(struct atmel_mci *host, struct mmc_data *data)
{
	if (data->flags & MMC_DATA_READ)
		atmci_writel(host, ATMEL_PDC_PTCR, ATMEL_PDC_RXTEN);
	else
		atmci_writel(host, ATMEL_PDC_PTCR, ATMEL_PDC_TXTEN);
}