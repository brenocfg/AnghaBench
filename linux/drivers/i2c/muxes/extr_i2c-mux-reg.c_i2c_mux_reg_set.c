#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int reg_size; int /*<<< orphan*/  reg; int /*<<< orphan*/  write_only; int /*<<< orphan*/  little_endian; } ;
struct regmux {TYPE_1__ data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ioread16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioread32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioread8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite16 (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite16be (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32be (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite8 (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2c_mux_reg_set(const struct regmux *mux, unsigned int chan_id)
{
	if (!mux->data.reg)
		return -EINVAL;

	/*
	 * Write to the register, followed by a read to ensure the write is
	 * completed on a "posted" bus, for example PCI or write buffers.
	 * The endianness of reading doesn't matter and the return data
	 * is not used.
	 */
	switch (mux->data.reg_size) {
	case 4:
		if (mux->data.little_endian)
			iowrite32(chan_id, mux->data.reg);
		else
			iowrite32be(chan_id, mux->data.reg);
		if (!mux->data.write_only)
			ioread32(mux->data.reg);
		break;
	case 2:
		if (mux->data.little_endian)
			iowrite16(chan_id, mux->data.reg);
		else
			iowrite16be(chan_id, mux->data.reg);
		if (!mux->data.write_only)
			ioread16(mux->data.reg);
		break;
	case 1:
		iowrite8(chan_id, mux->data.reg);
		if (!mux->data.write_only)
			ioread8(mux->data.reg);
		break;
	}

	return 0;
}