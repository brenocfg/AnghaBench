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
struct wilc {int /*<<< orphan*/  dev; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INTERNAL_READ ; 
 int N_OK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  le32_to_cpus (int /*<<< orphan*/ *) ; 
 int spi_cmd_complete (struct wilc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct spi_device* to_spi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spi_internal_read(struct wilc *wilc, u32 adr, u32 *data)
{
	struct spi_device *spi = to_spi_device(wilc->dev);
	int result;

	result = spi_cmd_complete(wilc, CMD_INTERNAL_READ, adr, (u8 *)data, 4,
				  0);
	if (result != N_OK) {
		dev_err(&spi->dev, "Failed internal read cmd...\n");
		return 0;
	}

	le32_to_cpus(data);

	return 1;
}