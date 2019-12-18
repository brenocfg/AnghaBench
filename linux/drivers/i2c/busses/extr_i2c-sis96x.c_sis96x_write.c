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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 int /*<<< orphan*/  outb (scalar_t__,scalar_t__) ; 
 scalar_t__ sis96x_smbus_base ; 

__attribute__((used)) static inline void sis96x_write(u8 reg, u8 data)
{
	outb(data, sis96x_smbus_base + reg) ;
}