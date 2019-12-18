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
struct dw_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spi_enable_chip (struct dw_spi*,int) ; 
 int /*<<< orphan*/  spi_mask_intr (struct dw_spi*,int) ; 

__attribute__((used)) static inline void spi_reset_chip(struct dw_spi *dws)
{
	spi_enable_chip(dws, 0);
	spi_mask_intr(dws, 0xff);
	spi_enable_chip(dws, 1);
}