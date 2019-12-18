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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct pvr2_hdw {int dummy; } ;

/* Variables and functions */
 int pvr2_i2c_read (struct pvr2_hdw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int pvr2_i2c_write (struct pvr2_hdw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int pvr2_i2c_basic_op(struct pvr2_hdw *hdw,
			     u8 i2c_addr,
			     u8 *wdata,
			     u16 wlen,
			     u8 *rdata,
			     u16 rlen)
{
	if (!rdata) rlen = 0;
	if (!wdata) wlen = 0;
	if (rlen || !wlen) {
		return pvr2_i2c_read(hdw,i2c_addr,wdata,wlen,rdata,rlen);
	} else {
		return pvr2_i2c_write(hdw,i2c_addr,wdata,wlen);
	}
}