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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 scalar_t__ SMB_DAT ; 
 scalar_t__ SMB_INDEX ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ sis5595_base ; 

__attribute__((used)) static void sis5595_write(u8 reg, u8 data)
{
	outb(reg, sis5595_base + SMB_INDEX);
	outb(data, sis5595_base + SMB_DAT);
}