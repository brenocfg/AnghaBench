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
struct slot {scalar_t__ p_sm_slot; } ;

/* Variables and functions */
 scalar_t__ SMBIOS_SLOT_WIDTH ; 
 int readb (scalar_t__) ; 

__attribute__((used)) static inline int is_slot64bit(struct slot *slot)
{
	return (readb(slot->p_sm_slot + SMBIOS_SLOT_WIDTH) == 0x06) ? 1 : 0;
}