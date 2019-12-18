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
struct spi_device {int dummy; } ;

/* Variables and functions */
 int b53_spi_clear_status (struct spi_device*) ; 
 int b53_spi_set_page (struct spi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int b53_prepare_reg_access(struct spi_device *spi, u8 page)
{
	int ret = b53_spi_clear_status(spi);

	if (ret)
		return ret;

	return b53_spi_set_page(spi, page);
}