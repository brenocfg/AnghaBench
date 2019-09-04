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
 int /*<<< orphan*/  IVTV_DEBUG_HI_I2C (char*) ; 
 int /*<<< orphan*/  IVTV_DEBUG_I2C (char*) ; 
 int ivtv_getscl (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_scldelay (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_setscl (struct ivtv*,int) ; 
 int /*<<< orphan*/  ivtv_setsda (struct ivtv*,int) ; 
 int /*<<< orphan*/  ivtv_waitscl (struct ivtv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivtv_waitsda (struct ivtv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ivtv_ack(struct ivtv *itv)
{
	int ret = 0;

	if (ivtv_getscl(itv) == 1) {
		IVTV_DEBUG_HI_I2C("SCL was high starting an ack\n");
		ivtv_setscl(itv, 0);
		if (!ivtv_waitscl(itv, 0)) {
			IVTV_DEBUG_I2C("Could not set SCL low starting an ack\n");
			return -EREMOTEIO;
		}
	}
	ivtv_setsda(itv, 1);
	ivtv_scldelay(itv);
	ivtv_setscl(itv, 1);
	if (!ivtv_waitsda(itv, 0)) {
		IVTV_DEBUG_I2C("Slave did not ack\n");
		ret = -EREMOTEIO;
	}
	ivtv_setscl(itv, 0);
	if (!ivtv_waitscl(itv, 0)) {
		IVTV_DEBUG_I2C("Failed to set SCL low after ACK\n");
		ret = -EREMOTEIO;
	}
	return ret;
}