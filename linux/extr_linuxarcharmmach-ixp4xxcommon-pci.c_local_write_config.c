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
typedef  int u32 ;

/* Variables and functions */
 int PCIBIOS_BAD_REGISTER_NUMBER ; 
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  crp_write (int,int) ; 
 int local_byte_lane_enable_bits (int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int) ; 

__attribute__((used)) static int local_write_config(int where, int size, u32 value)
{
	u32 n, byte_enables, data;
	pr_debug("local_write_config %#x to %d size %d\n", value, where, size);
	n = where % 4;
	byte_enables = local_byte_lane_enable_bits(n, size);
	if (byte_enables == 0xffffffff)
		return PCIBIOS_BAD_REGISTER_NUMBER;
	data = value << (8*n);
	crp_write((where & ~3) | byte_enables, data);
	return PCIBIOS_SUCCESSFUL;
}