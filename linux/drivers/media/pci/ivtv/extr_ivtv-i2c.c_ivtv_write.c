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
typedef  size_t u32 ;
struct ivtv {int dummy; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  IVTV_DEBUG_I2C (char*,unsigned char) ; 
 int ivtv_sendbyte (struct ivtv*,unsigned char) ; 
 int ivtv_start (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_stop (struct ivtv*) ; 

__attribute__((used)) static int ivtv_write(struct ivtv *itv, unsigned char addr, unsigned char *data, u32 len, int do_stop)
{
	int retry, ret = -EREMOTEIO;
	u32 i;

	for (retry = 0; ret != 0 && retry < 8; ++retry) {
		ret = ivtv_start(itv);

		if (ret == 0) {
			ret = ivtv_sendbyte(itv, addr<<1);
			for (i = 0; ret == 0 && i < len; ++i)
				ret = ivtv_sendbyte(itv, data[i]);
		}
		if (ret != 0 || do_stop) {
			ivtv_stop(itv);
		}
	}
	if (ret)
		IVTV_DEBUG_I2C("i2c write to %x failed\n", addr);
	return ret;
}