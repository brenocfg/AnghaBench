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
struct sun4i_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUN4I_INT_CTL_REG ; 
 int /*<<< orphan*/  sun4i_spi_read (struct sun4i_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun4i_spi_write (struct sun4i_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sun4i_spi_disable_interrupt(struct sun4i_spi *sspi, u32 mask)
{
	u32 reg = sun4i_spi_read(sspi, SUN4I_INT_CTL_REG);

	reg &= ~mask;
	sun4i_spi_write(sspi, SUN4I_INT_CTL_REG, reg);
}