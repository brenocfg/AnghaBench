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
typedef  scalar_t__ u16 ;
struct applespi_data {TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ET_RD_CRC ; 
 int /*<<< orphan*/  READ ; 
 scalar_t__ crc16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  dev_warn_ratelimited (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  trace_applespi_bad_crc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static bool applespi_verify_crc(struct applespi_data *applespi, u8 *buffer,
				size_t buflen)
{
	u16 crc;

	crc = crc16(0, buffer, buflen);
	if (crc) {
		dev_warn_ratelimited(&applespi->spi->dev,
				     "Received corrupted packet (crc mismatch)\n");
		trace_applespi_bad_crc(ET_RD_CRC, READ, buffer, buflen);

		return false;
	}

	return true;
}