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
struct max732x_chip {unsigned int mask_group_a; } ;

/* Variables and functions */

__attribute__((used)) static inline int is_group_a(struct max732x_chip *chip, unsigned off)
{
	return (1u << off) & chip->mask_group_a;
}