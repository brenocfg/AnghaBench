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
struct regmap_async {int dummy; } ;
struct regmap_async_spi {struct regmap_async core; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct regmap_async_spi* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct regmap_async *regmap_spi_async_alloc(void)
{
	struct regmap_async_spi *async_spi;

	async_spi = kzalloc(sizeof(*async_spi), GFP_KERNEL);
	if (!async_spi)
		return NULL;

	return &async_spi->core;
}