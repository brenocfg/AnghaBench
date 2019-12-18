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
typedef  size_t u8 ;
struct atp_unit {size_t* pciport; } ;

/* Variables and functions */
 size_t inb (size_t) ; 

__attribute__((used)) static inline u8 atp_readb_pci(struct atp_unit *atp, u8 channel, u8 reg)
{
	return inb(atp->pciport[channel] + reg);
}