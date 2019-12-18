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
#define  PHANA 135 
#define  PHANE 134 
#define  PHANLPA 133 
#define  PHCON1 132 
#define  PHCON2 131 
#define  PHSTAT1 130 
#define  PHSTAT2 129 
#define  PHSTAT3 128 

__attribute__((used)) static bool encx24j600_phymap_writeable(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case PHCON1:
	case PHCON2:
	case PHANA:
		return true;
	case PHSTAT1:
	case PHSTAT2:
	case PHSTAT3:
	case PHANLPA:
	case PHANE:
	default:
		return false;
	}
}