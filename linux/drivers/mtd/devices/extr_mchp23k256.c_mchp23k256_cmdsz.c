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
struct mchp23k256_flash {TYPE_1__* caps; } ;
struct TYPE_2__ {int addr_width; } ;

/* Variables and functions */

__attribute__((used)) static int mchp23k256_cmdsz(struct mchp23k256_flash *flash)
{
	return 1 + flash->caps->addr_width;
}