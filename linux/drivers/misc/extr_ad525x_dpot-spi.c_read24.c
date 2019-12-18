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
 int spi_read (void*,int*,int) ; 
 int /*<<< orphan*/  write24 (void*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read24(void *client, u8 reg)
{
	int ret;
	u8 buf_rx[3];

	write24(client, reg, 0);
	ret = spi_read(client, buf_rx, 3);
	if (ret < 0)
		return ret;

	return (buf_rx[1] << 8) |  buf_rx[2];
}