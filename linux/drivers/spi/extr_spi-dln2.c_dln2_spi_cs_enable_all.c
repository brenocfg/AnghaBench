#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct dln2_spi {TYPE_1__* master; } ;
struct TYPE_2__ {scalar_t__ num_chipselect; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENMASK (scalar_t__,int /*<<< orphan*/ ) ; 
 int dln2_spi_cs_enable (struct dln2_spi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dln2_spi_cs_enable_all(struct dln2_spi *dln2, bool enable)
{
	u8 cs_mask = GENMASK(dln2->master->num_chipselect - 1, 0);

	return dln2_spi_cs_enable(dln2, cs_mask, enable);
}