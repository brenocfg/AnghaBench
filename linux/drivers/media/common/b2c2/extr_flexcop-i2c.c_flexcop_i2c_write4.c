#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
struct flexcop_device {int /*<<< orphan*/  (* write_ibi_reg ) (struct flexcop_device*,int /*<<< orphan*/ ,TYPE_3__) ;} ;
struct TYPE_7__ {void* data4_reg; void* data3_reg; void* data2_reg; } ;
struct TYPE_8__ {int total_bytes; void* data1_reg; } ;
struct TYPE_9__ {scalar_t__ raw; TYPE_1__ tw_sm_c_104; TYPE_2__ tw_sm_c_100; } ;
typedef  TYPE_3__ flexcop_ibi_value ;

/* Variables and functions */
 int /*<<< orphan*/  deb_i2c (char*,scalar_t__,scalar_t__) ; 
 int flexcop_i2c_operation (struct flexcop_device*,TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (struct flexcop_device*,int /*<<< orphan*/ ,TYPE_3__) ; 
 int /*<<< orphan*/  tw_sm_c_104 ; 

__attribute__((used)) static int flexcop_i2c_write4(struct flexcop_device *fc,
		flexcop_ibi_value r100, u8 *buf)
{
	flexcop_ibi_value r104;
	int len = r100.tw_sm_c_100.total_bytes; /* remember total_bytes is buflen-1 */
	r104.raw = 0;

	/* there is at least one byte, otherwise we wouldn't be here */
	r100.tw_sm_c_100.data1_reg = buf[0];
	r104.tw_sm_c_104.data2_reg = len > 0 ? buf[1] : 0;
	r104.tw_sm_c_104.data3_reg = len > 1 ? buf[2] : 0;
	r104.tw_sm_c_104.data4_reg = len > 2 ? buf[3] : 0;

	deb_i2c("write: r100: %08x, r104: %08x\n", r100.raw, r104.raw);

	/* write the additional i2c data before doing the actual i2c operation */
	fc->write_ibi_reg(fc, tw_sm_c_104, r104);
	return flexcop_i2c_operation(fc, &r100);
}