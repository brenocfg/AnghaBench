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
struct mv88e6xxx_chip {TYPE_1__* info; } ;
struct TYPE_2__ {int invalid_port_mask; } ;

/* Variables and functions */
 int BIT (int) ; 

__attribute__((used)) static inline bool mv88e6xxx_is_invalid_port(struct mv88e6xxx_chip *chip, int port)
{
	return (chip->info->invalid_port_mask & BIT(port)) != 0;
}