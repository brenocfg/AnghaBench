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
 int ivtv_getsda (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_scldelay (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_setscl (struct ivtv*,int) ; 
 int /*<<< orphan*/  ivtv_setsda (struct ivtv*,int) ; 
 int /*<<< orphan*/  ivtv_waitscl (struct ivtv*,int) ; 
 int /*<<< orphan*/  ivtv_waitsda (struct ivtv*,int) ; 

__attribute__((used)) static int ivtv_start(struct ivtv *itv)
{
	int sda;

	sda = ivtv_getsda(itv);
	if (sda != 1) {
		IVTV_DEBUG_HI_I2C("SDA was low at start\n");
		ivtv_setsda(itv, 1);
		if (!ivtv_waitsda(itv, 1)) {
			IVTV_DEBUG_I2C("SDA stuck low\n");
			return -EREMOTEIO;
		}
	}
	if (ivtv_getscl(itv) != 1) {
		ivtv_setscl(itv, 1);
		if (!ivtv_waitscl(itv, 1)) {
			IVTV_DEBUG_I2C("SCL stuck low at start\n");
			return -EREMOTEIO;
		}
	}
	ivtv_setsda(itv, 0);
	ivtv_scldelay(itv);
	return 0;
}