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
typedef  int u8 ;
struct scatterlist {int dummy; } ;
struct mmc_test_card {int* scratch; int* buffer; } ;

/* Variables and functions */
 int BUFFER_SIZE ; 
 int EINVAL ; 
 int RESULT_FAIL ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int mmc_test_buffer_transfer (struct mmc_test_card*,int*,unsigned int,int,int /*<<< orphan*/ ) ; 
 int mmc_test_set_blksize (struct mmc_test_card*,int) ; 
 int mmc_test_simple_transfer (struct mmc_test_card*,struct scatterlist*,unsigned int,unsigned int,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  sg_copy_from_buffer (struct scatterlist*,unsigned int,int*,int) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (struct scatterlist*,unsigned int,int*,int) ; 

__attribute__((used)) static int mmc_test_transfer(struct mmc_test_card *test,
	struct scatterlist *sg, unsigned sg_len, unsigned dev_addr,
	unsigned blocks, unsigned blksz, int write)
{
	int ret, i;
	unsigned long flags;

	if (write) {
		for (i = 0; i < blocks * blksz; i++)
			test->scratch[i] = i;
	} else {
		memset(test->scratch, 0, BUFFER_SIZE);
	}
	local_irq_save(flags);
	sg_copy_from_buffer(sg, sg_len, test->scratch, BUFFER_SIZE);
	local_irq_restore(flags);

	ret = mmc_test_set_blksize(test, blksz);
	if (ret)
		return ret;

	ret = mmc_test_simple_transfer(test, sg, sg_len, dev_addr,
		blocks, blksz, write);
	if (ret)
		return ret;

	if (write) {
		int sectors;

		ret = mmc_test_set_blksize(test, 512);
		if (ret)
			return ret;

		sectors = (blocks * blksz + 511) / 512;
		if ((sectors * 512) == (blocks * blksz))
			sectors++;

		if ((sectors * 512) > BUFFER_SIZE)
			return -EINVAL;

		memset(test->buffer, 0, sectors * 512);

		for (i = 0; i < sectors; i++) {
			ret = mmc_test_buffer_transfer(test,
				test->buffer + i * 512,
				dev_addr + i, 512, 0);
			if (ret)
				return ret;
		}

		for (i = 0; i < blocks * blksz; i++) {
			if (test->buffer[i] != (u8)i)
				return RESULT_FAIL;
		}

		for (; i < sectors * 512; i++) {
			if (test->buffer[i] != 0xDF)
				return RESULT_FAIL;
		}
	} else {
		local_irq_save(flags);
		sg_copy_to_buffer(sg, sg_len, test->scratch, BUFFER_SIZE);
		local_irq_restore(flags);
		for (i = 0; i < blocks * blksz; i++) {
			if (test->scratch[i] != (u8)i)
				return RESULT_FAIL;
		}
	}

	return 0;
}