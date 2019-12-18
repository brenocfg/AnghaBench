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
struct ti_qspi {scalar_t__ base; } ;

/* Variables and functions */
 unsigned long readl (scalar_t__) ; 

__attribute__((used)) static inline unsigned long ti_qspi_read(struct ti_qspi *qspi,
		unsigned long reg)
{
	return readl(qspi->base + reg);
}