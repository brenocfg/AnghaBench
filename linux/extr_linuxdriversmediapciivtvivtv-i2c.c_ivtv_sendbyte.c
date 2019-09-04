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
struct ivtv {int dummy; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  IVTV_DEBUG_HI_I2C (char*,unsigned char) ; 
 int /*<<< orphan*/  IVTV_DEBUG_I2C (char*) ; 
 int ivtv_ack (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_setscl (struct ivtv*,int) ; 
 int /*<<< orphan*/  ivtv_setsda (struct ivtv*,int) ; 
 int /*<<< orphan*/  ivtv_waitscl (struct ivtv*,int) ; 
 int /*<<< orphan*/  ivtv_waitsda (struct ivtv*,int) ; 

__attribute__((used)) static int ivtv_sendbyte(struct ivtv *itv, unsigned char byte)
{
	int i, bit;

	IVTV_DEBUG_HI_I2C("write %x\n",byte);
	for (i = 0; i < 8; ++i, byte<<=1) {
		ivtv_setscl(itv, 0);
		if (!ivtv_waitscl(itv, 0)) {
			IVTV_DEBUG_I2C("Error setting SCL low\n");
			return -EREMOTEIO;
		}
		bit = (byte>>7)&1;
		ivtv_setsda(itv, bit);
		if (!ivtv_waitsda(itv, bit)) {
			IVTV_DEBUG_I2C("Error setting SDA\n");
			return -EREMOTEIO;
		}
		ivtv_setscl(itv, 1);
		if (!ivtv_waitscl(itv, 1)) {
			IVTV_DEBUG_I2C("Slave not ready for bit\n");
			return -EREMOTEIO;
		}
	}
	ivtv_setscl(itv, 0);
	if (!ivtv_waitscl(itv, 0)) {
		IVTV_DEBUG_I2C("Error setting SCL low\n");
		return -EREMOTEIO;
	}
	return ivtv_ack(itv);
}