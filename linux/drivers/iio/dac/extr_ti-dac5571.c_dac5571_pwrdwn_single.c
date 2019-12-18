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
struct dac5571_data {int* buf; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int DAC5571_SINGLE_PWRDWN_BITS ; 
 int EIO ; 
 int i2c_master_send (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int dac5571_pwrdwn_single(struct dac5571_data *data, int channel, u8 pwrdwn)
{
	data->buf[1] = 0;
	data->buf[0] = pwrdwn << DAC5571_SINGLE_PWRDWN_BITS;

	if (i2c_master_send(data->client, data->buf, 2) != 2)
		return -EIO;

	return 0;
}