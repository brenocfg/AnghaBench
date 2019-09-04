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
typedef  int u8 ;

/* Variables and functions */
 unsigned short PCI_DEVICE_ID_JMICRON_JMC250 ; 

__attribute__((used)) static inline int is_buggy250(unsigned short device, u8 chiprev)
{
	return device == PCI_DEVICE_ID_JMICRON_JMC250 && chiprev == 0x11;
}