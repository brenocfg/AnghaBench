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
struct p54s_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_ADRS_ARM_INTERRUPTS ; 
 int /*<<< orphan*/  SPI_TARGET_INT_SLEEP ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p54spi_write32 (struct p54s_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void p54spi_sleep(struct p54s_priv *priv)
{
	p54spi_write32(priv, SPI_ADRS_ARM_INTERRUPTS,
		       cpu_to_le32(SPI_TARGET_INT_SLEEP));
}