#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct adv748x_state {TYPE_1__* client; } ;
struct TYPE_2__ {int addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV748X_IO_CHIP_REV_ID_1 ; 
 int /*<<< orphan*/  ADV748X_IO_CHIP_REV_ID_2 ; 
 int EIO ; 
 int /*<<< orphan*/  adv_err (struct adv748x_state*,char*) ; 
 int /*<<< orphan*/  adv_info (struct adv748x_state*,char*,int,int,int) ; 
 int io_read (struct adv748x_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adv748x_identify_chip(struct adv748x_state *state)
{
	int msb, lsb;

	lsb = io_read(state, ADV748X_IO_CHIP_REV_ID_1);
	msb = io_read(state, ADV748X_IO_CHIP_REV_ID_2);

	if (lsb < 0 || msb < 0) {
		adv_err(state, "Failed to read chip revision\n");
		return -EIO;
	}

	adv_info(state, "chip found @ 0x%02x revision %02x%02x\n",
		 state->client->addr << 1, lsb, msb);

	return 0;
}