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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  inl (int) ; 
 int /*<<< orphan*/  outl (int,int) ; 

u32 read_pci_config(u8 bus, u8 slot, u8 func, u8 offset)
{
	u32 v;
	outl(0x80000000 | (bus<<16) | (slot<<11) | (func<<8) | offset, 0xcf8);
	v = inl(0xcfc);
	return v;
}