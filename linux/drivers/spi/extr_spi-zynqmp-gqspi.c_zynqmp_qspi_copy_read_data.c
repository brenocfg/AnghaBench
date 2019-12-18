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
typedef  int /*<<< orphan*/  ulong ;
typedef  scalar_t__ u8 ;
struct zynqmp_qspi {int /*<<< orphan*/  bytes_to_receive; int /*<<< orphan*/  rxbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void zynqmp_qspi_copy_read_data(struct zynqmp_qspi *xqspi,
				       ulong data, u8 size)
{
	memcpy(xqspi->rxbuf, &data, size);
	xqspi->rxbuf += size;
	xqspi->bytes_to_receive -= size;
}