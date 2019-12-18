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
struct spi_master {int dummy; } ;
struct spi_bitbang {struct spi_master* master; } ;

/* Variables and functions */
 int spi_bitbang_init (struct spi_bitbang*) ; 
 int /*<<< orphan*/  spi_master_get (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 int spi_register_master (int /*<<< orphan*/ ) ; 

int spi_bitbang_start(struct spi_bitbang *bitbang)
{
	struct spi_master *master = bitbang->master;
	int ret;

	ret = spi_bitbang_init(bitbang);
	if (ret)
		return ret;

	/* driver may get busy before register() returns, especially
	 * if someone registered boardinfo for devices
	 */
	ret = spi_register_master(spi_master_get(master));
	if (ret)
		spi_master_put(master);

	return ret;
}