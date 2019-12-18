#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int member_0; int member_1; int member_2; int member_3; int member_4; } ;
typedef  TYPE_1__ u8 ;
struct i2c_msg {int addr; int len; TYPE_1__* buf; int /*<<< orphan*/  flags; } ;
struct cx88_core {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__**) ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int) ; 

__attribute__((used)) static void dvico_fusionhdtv_hybrid_init(struct cx88_core *core)
{
	struct i2c_msg msg = { .addr = 0x45, .flags = 0 };
	int i, err;
	static u8 init_bufs[13][5] = {
		{ 0x10, 0x00, 0x20, 0x01, 0x03 },
		{ 0x10, 0x10, 0x01, 0x00, 0x21 },
		{ 0x10, 0x10, 0x10, 0x00, 0xCA },
		{ 0x10, 0x10, 0x12, 0x00, 0x08 },
		{ 0x10, 0x10, 0x13, 0x00, 0x0A },
		{ 0x10, 0x10, 0x16, 0x01, 0xC0 },
		{ 0x10, 0x10, 0x22, 0x01, 0x3D },
		{ 0x10, 0x10, 0x73, 0x01, 0x2E },
		{ 0x10, 0x10, 0x72, 0x00, 0xC5 },
		{ 0x10, 0x10, 0x71, 0x01, 0x97 },
		{ 0x10, 0x10, 0x70, 0x00, 0x0F },
		{ 0x10, 0x10, 0xB0, 0x00, 0x01 },
		{ 0x03, 0x0C },
	};

	for (i = 0; i < ARRAY_SIZE(init_bufs); i++) {
		msg.buf = init_bufs[i];
		msg.len = (i != 12 ? 5 : 2);
		err = i2c_transfer(&core->i2c_adap, &msg, 1);
		if (err != 1) {
			pr_warn("dvico_fusionhdtv_hybrid_init buf %d failed (err = %d)!\n",
				i, err);
			return;
		}
	}
}