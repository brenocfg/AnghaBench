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
struct spi_nor {unsigned int page_size; } ;
typedef  unsigned int loff_t ;

/* Variables and functions */

__attribute__((used)) static loff_t spi_nor_s3an_addr_convert(struct spi_nor *nor, unsigned int addr)
{
	unsigned int offset;
	unsigned int page;

	offset = addr % nor->page_size;
	page = addr / nor->page_size;
	page <<= (nor->page_size > 512) ? 10 : 9;

	return page | offset;
}