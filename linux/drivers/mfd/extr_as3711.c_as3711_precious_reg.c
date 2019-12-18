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
#define  AS3711_INTERRUPT_STATUS_1 130 
#define  AS3711_INTERRUPT_STATUS_2 129 
#define  AS3711_INTERRUPT_STATUS_3 128 

__attribute__((used)) static bool as3711_precious_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case AS3711_INTERRUPT_STATUS_1:
	case AS3711_INTERRUPT_STATUS_2:
	case AS3711_INTERRUPT_STATUS_3:
		return true;
	}
	return false;
}