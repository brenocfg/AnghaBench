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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {unsigned int regs; } ;
struct zevio_gpio {TYPE_1__ chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOMEM (unsigned int) ; 
 unsigned int ZEVIO_GPIO_SECTION_SIZE ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 zevio_gpio_port_get(struct zevio_gpio *c, unsigned pin,
					unsigned port_offset)
{
	unsigned section_offset = ((pin >> 3) & 3)*ZEVIO_GPIO_SECTION_SIZE;
	return readl(IOMEM(c->chip.regs + section_offset + port_offset));
}