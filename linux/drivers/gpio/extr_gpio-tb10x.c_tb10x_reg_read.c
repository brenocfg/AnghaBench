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
struct tb10x_gpio {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 

__attribute__((used)) static inline u32 tb10x_reg_read(struct tb10x_gpio *gpio, unsigned int offs)
{
	return ioread32(gpio->base + offs);
}