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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx25840_and_or (struct i2c_client*,int,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void cx25836_initialize(struct i2c_client *client)
{
	/* reset configuration is described on page 3-77 of the CX25836 datasheet */
	/* 2. */
	cx25840_and_or(client, 0x000, ~0x01, 0x01);
	cx25840_and_or(client, 0x000, ~0x01, 0x00);
	/* 3a. */
	cx25840_and_or(client, 0x15a, ~0x70, 0x00);
	/* 3b. */
	cx25840_and_or(client, 0x15b, ~0x1e, 0x06);
	/* 3c. */
	cx25840_and_or(client, 0x159, ~0x02, 0x02);
	/* 3d. */
	udelay(10);
	/* 3e. */
	cx25840_and_or(client, 0x159, ~0x02, 0x00);
	/* 3f. */
	cx25840_and_or(client, 0x159, ~0xc0, 0xc0);
	/* 3g. */
	cx25840_and_or(client, 0x159, ~0x01, 0x00);
	cx25840_and_or(client, 0x159, ~0x01, 0x01);
	/* 3h. */
	cx25840_and_or(client, 0x15b, ~0x1e, 0x10);
}