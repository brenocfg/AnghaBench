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
struct sg_mapping_iter {int dummy; } ;
struct mmc_data {size_t blocks; int blksz; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;
struct cb710_slot {scalar_t__ iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  CB710_MMC_C2_READ_PIO_SIZE_MASK ; 
 int /*<<< orphan*/  CB710_MMC_CONFIG2_PORT ; 
 scalar_t__ CB710_MMC_DATA_PORT ; 
 int /*<<< orphan*/  CB710_MMC_S1_PIO_TRANSFER_DONE ; 
 int CB710_MMC_S2_FIFO_EMPTY ; 
 int /*<<< orphan*/  CB710_MMC_STATUS2_PORT ; 
 int EINVAL ; 
 int /*<<< orphan*/  SG_MITER_FROM_SG ; 
 int /*<<< orphan*/  cb710_modify_port_8 (struct cb710_slot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cb710_read_port_8 (struct cb710_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cb710_sg_dwiter_read_to_io (struct sg_mapping_iter*,scalar_t__,int) ; 
 int cb710_wait_for_event (struct cb710_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_miter_start (struct sg_mapping_iter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_miter_stop (struct sg_mapping_iter*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int cb710_mmc_send(struct cb710_slot *slot, struct mmc_data *data)
{
	struct sg_mapping_iter miter;
	size_t len, blocks = data->blocks;
	int err = 0;

	/* TODO: I don't know how/if the hardware handles multiple
	 * non-16B-boundary blocks */
	if (unlikely(data->blocks > 1 && data->blksz & 15))
		return -EINVAL;

	sg_miter_start(&miter, data->sg, data->sg_len, SG_MITER_FROM_SG);

	cb710_modify_port_8(slot, CB710_MMC_CONFIG2_PORT,
		0, CB710_MMC_C2_READ_PIO_SIZE_MASK);

	while (blocks-- > 0) {
		len = (data->blksz + 15) >> 4;
		do {
			if (!(cb710_read_port_8(slot, CB710_MMC_STATUS2_PORT)
			    & CB710_MMC_S2_FIFO_EMPTY)) {
				err = cb710_wait_for_event(slot,
					CB710_MMC_S1_PIO_TRANSFER_DONE);
				if (err)
					goto out;
			}
			cb710_sg_dwiter_read_to_io(&miter,
				slot->iobase + CB710_MMC_DATA_PORT, 4);
		} while (--len);
	}
out:
	sg_miter_stop(&miter);
	return err;
}