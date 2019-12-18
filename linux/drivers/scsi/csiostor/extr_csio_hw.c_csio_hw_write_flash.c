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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int sf_size; } ;
struct csio_hw {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  SF_OP_A ; 
 int SF_PAGE_SIZE ; 
 int SF_PROG_PAGE ; 
 int SF_WR_ENABLE ; 
 int /*<<< orphan*/  csio_err (struct csio_hw*,char*,int) ; 
 int csio_hw_flash_wait_op (struct csio_hw*,int,int) ; 
 int csio_hw_read_flash (struct csio_hw*,int,int /*<<< orphan*/ ,int*,int) ; 
 int csio_hw_sf1_write (struct csio_hw*,int,int,int,int) ; 
 int /*<<< orphan*/  csio_wr_reg32 (struct csio_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int min (int,unsigned int) ; 
 int swab32 (int) ; 

__attribute__((used)) static int
csio_hw_write_flash(struct csio_hw *hw, uint32_t addr,
		    uint32_t n, const uint8_t *data)
{
	int ret = -EINVAL;
	uint32_t buf[64];
	uint32_t i, c, left, val, offset = addr & 0xff;

	if (addr >= hw->params.sf_size || offset + n > SF_PAGE_SIZE)
		return -EINVAL;

	val = swab32(addr) | SF_PROG_PAGE;

	ret = csio_hw_sf1_write(hw, 1, 0, 1, SF_WR_ENABLE);
	if (ret != 0)
		goto unlock;

	ret = csio_hw_sf1_write(hw, 4, 1, 1, val);
	if (ret != 0)
		goto unlock;

	for (left = n; left; left -= c) {
		c = min(left, 4U);
		for (val = 0, i = 0; i < c; ++i)
			val = (val << 8) + *data++;

		ret = csio_hw_sf1_write(hw, c, c != left, 1, val);
		if (ret)
			goto unlock;
	}
	ret = csio_hw_flash_wait_op(hw, 8, 1);
	if (ret)
		goto unlock;

	csio_wr_reg32(hw, 0, SF_OP_A);    /* unlock SF */

	/* Read the page to verify the write succeeded */
	ret = csio_hw_read_flash(hw, addr & ~0xff, ARRAY_SIZE(buf), buf, 1);
	if (ret)
		return ret;

	if (memcmp(data - n, (uint8_t *)buf + offset, n)) {
		csio_err(hw,
			 "failed to correctly write the flash page at %#x\n",
			 addr);
		return -EINVAL;
	}

	return 0;

unlock:
	csio_wr_reg32(hw, 0, SF_OP_A);    /* unlock SF */
	return ret;
}