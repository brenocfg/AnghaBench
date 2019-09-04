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
struct hisi_lpc_dev {TYPE_1__* io_host; } ;
struct TYPE_2__ {unsigned long io_start; unsigned long hw_start; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long hisi_lpc_pio_to_addr(struct hisi_lpc_dev *lpcdev,
					  unsigned long pio)
{
	return pio - lpcdev->io_host->io_start + lpcdev->io_host->hw_start;
}