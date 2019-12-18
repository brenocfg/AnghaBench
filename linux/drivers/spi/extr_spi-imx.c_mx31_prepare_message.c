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
struct spi_message {int dummy; } ;
struct spi_imx_data {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int mx31_prepare_message(struct spi_imx_data *spi_imx,
				struct spi_message *msg)
{
	return 0;
}