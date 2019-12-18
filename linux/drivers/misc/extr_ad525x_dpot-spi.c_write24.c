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
typedef  int u16 ;

/* Variables and functions */
 int spi_write (void*,int*,int) ; 

__attribute__((used)) static int write24(void *client, u8 reg, u16 val)
{
	u8 data[3] = {reg, val >> 8, val};

	return spi_write(client, data, 3);
}