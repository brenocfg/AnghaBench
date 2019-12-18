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
typedef  int u32 ;
struct hspi_priv {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SPSR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int hspi_read (struct hspi_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int hspi_status_check_timeout(struct hspi_priv *hspi, u32 mask, u32 val)
{
	int t = 256;

	while (t--) {
		if ((mask & hspi_read(hspi, SPSR)) == val)
			return 0;

		udelay(10);
	}

	dev_err(hspi->dev, "timeout\n");
	return -ETIMEDOUT;
}