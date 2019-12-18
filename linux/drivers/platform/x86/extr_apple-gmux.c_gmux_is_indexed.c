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
typedef  int u16 ;
struct apple_gmux_data {scalar_t__ iostart; } ;

/* Variables and functions */
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static bool gmux_is_indexed(struct apple_gmux_data *gmux_data)
{
	u16 val;

	outb(0xaa, gmux_data->iostart + 0xcc);
	outb(0x55, gmux_data->iostart + 0xcd);
	outb(0x00, gmux_data->iostart + 0xce);

	val = inb(gmux_data->iostart + 0xcc) |
		(inb(gmux_data->iostart + 0xcd) << 8);

	if (val == 0x55aa)
		return true;

	return false;
}