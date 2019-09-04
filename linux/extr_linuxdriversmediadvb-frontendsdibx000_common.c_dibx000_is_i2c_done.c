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
struct dibx000_i2c_master {scalar_t__ base_reg; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int dibx000_read_word (struct dibx000_i2c_master*,scalar_t__) ; 

__attribute__((used)) static int dibx000_is_i2c_done(struct dibx000_i2c_master *mst)
{
	int i = 100;
	u16 status;

	while (((status = dibx000_read_word(mst, mst->base_reg + 2)) & 0x0100) == 0 && --i > 0)
		;

	/* i2c timed out */
	if (i == 0)
		return -EREMOTEIO;

	/* no acknowledge */
	if ((status & 0x0080) == 0)
		return -EREMOTEIO;

	return 0;
}