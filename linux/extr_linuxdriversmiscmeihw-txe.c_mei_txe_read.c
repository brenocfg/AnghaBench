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
typedef  unsigned long u32 ;
struct mei_txe_hw {int dummy; } ;
struct mei_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long MEI_SLOT_SIZE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 
 unsigned long mei_txe_out_data_read (struct mei_device*,unsigned long) ; 
 int /*<<< orphan*/  mei_txe_output_ready_set (struct mei_txe_hw*) ; 
 int /*<<< orphan*/  memcpy (unsigned long*,unsigned long*,unsigned long) ; 
 struct mei_txe_hw* to_txe_hw (struct mei_device*) ; 

__attribute__((used)) static int mei_txe_read(struct mei_device *dev,
		unsigned char *buf, unsigned long len)
{

	struct mei_txe_hw *hw = to_txe_hw(dev);
	u32 *reg_buf, reg;
	u32 rem;
	u32 i;

	if (WARN_ON(!buf || !len))
		return -EINVAL;

	reg_buf = (u32 *)buf;
	rem = len & 0x3;

	dev_dbg(dev->dev, "buffer-length = %lu buf[0]0x%08X\n",
		len, mei_txe_out_data_read(dev, 0));

	for (i = 0; i < len / MEI_SLOT_SIZE; i++) {
		/* skip header: index starts from 1 */
		reg = mei_txe_out_data_read(dev, i + 1);
		dev_dbg(dev->dev, "buf[%d] = 0x%08X\n", i, reg);
		*reg_buf++ = reg;
	}

	if (rem) {
		reg = mei_txe_out_data_read(dev, i + 1);
		memcpy(reg_buf, &reg, rem);
	}

	mei_txe_output_ready_set(hw);
	return 0;
}