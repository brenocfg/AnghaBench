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
struct atmel_mci {scalar_t__ data_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDC_FIRST_BUF ; 
 int /*<<< orphan*/  PDC_SECOND_BUF ; 
 int /*<<< orphan*/  atmci_pdc_set_single_buf (struct atmel_mci*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atmci_pdc_set_both_buf(struct atmel_mci *host, int dir)
{
	atmci_pdc_set_single_buf(host, dir, PDC_FIRST_BUF);
	if (host->data_size)
		atmci_pdc_set_single_buf(host, dir, PDC_SECOND_BUF);
}