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
 int spi_write (void*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int write16(void *client, u8 reg, u8 val)
{
	u8 data[2] = {reg, val};

	return spi_write(client, data, 2);
}