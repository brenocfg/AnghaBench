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
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int APBREG_BSR_SARAC ; 
 unsigned int APBREG_PAER ; 
 int /*<<< orphan*/  sta2x11_apbreg_readable_reg (struct device*,unsigned int) ; 

__attribute__((used)) static bool sta2x11_apbreg_writeable_reg(struct device *dev, unsigned int reg)
{
	if (reg >= APBREG_BSR_SARAC)
		reg -= APBREG_BSR_SARAC;
	if (!sta2x11_apbreg_readable_reg(dev, reg))
		return false;
	return reg != APBREG_PAER;
}