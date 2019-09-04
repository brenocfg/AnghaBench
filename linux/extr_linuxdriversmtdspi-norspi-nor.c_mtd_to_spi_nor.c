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
struct spi_nor {int dummy; } ;
struct mtd_info {struct spi_nor* priv; } ;

/* Variables and functions */

__attribute__((used)) static inline struct spi_nor *mtd_to_spi_nor(struct mtd_info *mtd)
{
	return mtd->priv;
}