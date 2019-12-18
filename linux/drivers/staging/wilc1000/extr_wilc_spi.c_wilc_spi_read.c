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
typedef  int u32 ;
struct wilc {int /*<<< orphan*/  dev; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DMA_EXT_READ ; 
 int N_OK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int spi_cmd_complete (struct wilc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct spi_device* to_spi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wilc_spi_read(struct wilc *wilc, u32 addr, u8 *buf, u32 size)
{
	struct spi_device *spi = to_spi_device(wilc->dev);
	int result;

	if (size <= 4)
		return 0;

	result = spi_cmd_complete(wilc, CMD_DMA_EXT_READ, addr, buf, size, 0);
	if (result != N_OK) {
		dev_err(&spi->dev, "Failed cmd, read block (%08x)...\n", addr);
		return 0;
	}

	return 1;
}