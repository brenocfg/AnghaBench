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
struct spi_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void setmosi(struct spi_device *s, int is_on)
{
	/* FIXME update D7 ... this way we can put the chip
	 * into shutdown mode and read the manufacturer ID,
	 * but we can't put it back into operational mode.
	 */
}