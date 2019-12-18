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
typedef  int u8 ;
struct applespi_data {int /*<<< orphan*/  tx_status; TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPLESPI_STATUS_SIZE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,...) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool applespi_check_write_status(struct applespi_data *applespi,
					       int sts)
{
	static u8 status_ok[] = { 0xac, 0x27, 0x68, 0xd5 };

	if (sts < 0) {
		dev_warn(&applespi->spi->dev, "Error writing to device: %d\n",
			 sts);
		return false;
	}

	if (memcmp(applespi->tx_status, status_ok, APPLESPI_STATUS_SIZE)) {
		dev_warn(&applespi->spi->dev, "Error writing to device: %*ph\n",
			 APPLESPI_STATUS_SIZE, applespi->tx_status);
		return false;
	}

	return true;
}