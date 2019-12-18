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
struct geni_se {int dummy; } ;
struct spi_geni_master {int /*<<< orphan*/  dev; int /*<<< orphan*/  xfer_done; int /*<<< orphan*/  cur_mcmd; struct geni_se se; } ;
struct spi_device {int mode; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CS ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  SPI_CS_ASSERT ; 
 int /*<<< orphan*/  SPI_CS_DEASSERT ; 
 int SPI_CS_HIGH ; 
 struct spi_master* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  geni_se_setup_m_cmd (struct geni_se*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_fifo_timeout (struct spi_master*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 struct spi_geni_master* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spi_geni_set_cs(struct spi_device *slv, bool set_flag)
{
	struct spi_geni_master *mas = spi_master_get_devdata(slv->master);
	struct spi_master *spi = dev_get_drvdata(mas->dev);
	struct geni_se *se = &mas->se;
	unsigned long time_left;

	reinit_completion(&mas->xfer_done);
	pm_runtime_get_sync(mas->dev);
	if (!(slv->mode & SPI_CS_HIGH))
		set_flag = !set_flag;

	mas->cur_mcmd = CMD_CS;
	if (set_flag)
		geni_se_setup_m_cmd(se, SPI_CS_ASSERT, 0);
	else
		geni_se_setup_m_cmd(se, SPI_CS_DEASSERT, 0);

	time_left = wait_for_completion_timeout(&mas->xfer_done, HZ);
	if (!time_left)
		handle_fifo_timeout(spi, NULL);

	pm_runtime_put(mas->dev);
}