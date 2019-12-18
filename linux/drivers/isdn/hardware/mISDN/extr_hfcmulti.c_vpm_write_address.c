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
struct hfc_multi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpld_write_reg (struct hfc_multi*,int,int) ; 

__attribute__((used)) static inline void
vpm_write_address(struct hfc_multi *hc, unsigned short addr)
{
	cpld_write_reg(hc, 0, 0xff & addr);
	cpld_write_reg(hc, 1, 0x01 & (addr >> 8));
}