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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct anarion_gmac {scalar_t__ ctl_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void gmac_write_reg(struct anarion_gmac *gmac, uint8_t reg, uint32_t val)
{
	writel(val, (void *)(gmac->ctl_block + reg));
}