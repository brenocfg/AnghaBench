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
typedef  int /*<<< orphan*/  u32 ;
struct sun6i_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUN6I_INT_CTL_REG ; 
 int /*<<< orphan*/  sun6i_spi_read (struct sun6i_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun6i_spi_write (struct sun6i_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sun6i_spi_enable_interrupt(struct sun6i_spi *sspi, u32 mask)
{
	u32 reg = sun6i_spi_read(sspi, SUN6I_INT_CTL_REG);

	reg |= mask;
	sun6i_spi_write(sspi, SUN6I_INT_CTL_REG, reg);
}