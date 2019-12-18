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
typedef  int u32 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int CX23885_AV ; 
 int CX23887_AV ; 
 int CX23888_AV ; 
 int cx25840_read4 (struct i2c_client*,int) ; 
 int /*<<< orphan*/  cx25840_write (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  v4l_err (struct i2c_client*,char*) ; 

__attribute__((used)) static u32 get_cx2388x_ident(struct i2c_client *client)
{
	u32 ret;

	/* Come out of digital power down */
	cx25840_write(client, 0x000, 0);

	/*
	 * Detecting whether the part is cx23885/7/8 is more
	 * difficult than it needs to be. No ID register. Instead we
	 * probe certain registers indicated in the datasheets to look
	 * for specific defaults that differ between the silicon designs.
	 */

	/* It's either 885/7 if the IR Tx Clk Divider register exists */
	if (cx25840_read4(client, 0x204) & 0xffff) {
		/*
		 * CX23885 returns bogus repetitive byte values for the DIF,
		 * which doesn't exist for it. (Ex. 8a8a8a8a or 31313131)
		 */
		ret = cx25840_read4(client, 0x300);
		if (((ret & 0xffff0000) >> 16) == (ret & 0xffff)) {
			/* No DIF */
			ret = CX23885_AV;
		} else {
			/*
			 * CX23887 has a broken DIF, but the registers
			 * appear valid (but unused), good enough to detect.
			 */
			ret = CX23887_AV;
		}
	} else if (cx25840_read4(client, 0x300) & 0x0fffffff) {
		/* DIF PLL Freq Word reg exists; chip must be a CX23888 */
		ret = CX23888_AV;
	} else {
		v4l_err(client, "Unable to detect h/w, assuming cx23887\n");
		ret = CX23887_AV;
	}

	/* Back into digital power down */
	cx25840_write(client, 0x000, 2);
	return ret;
}