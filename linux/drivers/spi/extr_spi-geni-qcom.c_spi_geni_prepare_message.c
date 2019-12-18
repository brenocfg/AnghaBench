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
struct spi_message {int /*<<< orphan*/  spi; } ;
struct spi_master {int dummy; } ;
struct geni_se {int dummy; } ;
struct spi_geni_master {int /*<<< orphan*/  dev; struct geni_se se; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENI_SE_FIFO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  geni_se_select_mode (struct geni_se*,int /*<<< orphan*/ ) ; 
 int setup_fifo_params (int /*<<< orphan*/ ,struct spi_master*) ; 
 struct spi_geni_master* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int spi_geni_prepare_message(struct spi_master *spi,
					struct spi_message *spi_msg)
{
	int ret;
	struct spi_geni_master *mas = spi_master_get_devdata(spi);
	struct geni_se *se = &mas->se;

	geni_se_select_mode(se, GENI_SE_FIFO);
	ret = setup_fifo_params(spi_msg->spi, spi);
	if (ret)
		dev_err(mas->dev, "Couldn't select mode %d\n", ret);
	return ret;
}