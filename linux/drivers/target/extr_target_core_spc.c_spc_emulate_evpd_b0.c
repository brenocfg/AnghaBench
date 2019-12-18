#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int block_size; int optimal_sectors; int max_unmap_lba_count; int max_unmap_block_desc_count; int unmap_granularity; int unmap_granularity_alignment; int /*<<< orphan*/  max_write_same_len; int /*<<< orphan*/  hw_max_sectors; scalar_t__ emulate_caw; scalar_t__ emulate_tpws; scalar_t__ emulate_tpu; } ;
struct se_device {TYPE_3__ dev_attrib; TYPE_2__* transport; } ;
struct se_cmd {TYPE_1__* se_tfo; struct se_device* se_dev; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
struct TYPE_5__ {unsigned char (* get_device_type ) (struct se_device*) ;int (* get_io_min ) (struct se_device*) ;int (* get_io_opt ) (struct se_device*) ;} ;
struct TYPE_4__ {int max_data_sg_nents; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int min_not_zero (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_be16 (int,unsigned char*) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int,unsigned char*) ; 
 int /*<<< orphan*/  put_unaligned_be64 (int /*<<< orphan*/ ,unsigned char*) ; 
 unsigned char stub1 (struct se_device*) ; 
 int stub2 (struct se_device*) ; 
 int stub3 (struct se_device*) ; 

__attribute__((used)) static sense_reason_t
spc_emulate_evpd_b0(struct se_cmd *cmd, unsigned char *buf)
{
	struct se_device *dev = cmd->se_dev;
	u32 mtl = 0;
	int have_tp = 0, opt, min;

	/*
	 * Following spc3r22 section 6.5.3 Block Limits VPD page, when
	 * emulate_tpu=1 or emulate_tpws=1 we will be expect a
	 * different page length for Thin Provisioning.
	 */
	if (dev->dev_attrib.emulate_tpu || dev->dev_attrib.emulate_tpws)
		have_tp = 1;

	buf[0] = dev->transport->get_device_type(dev);
	buf[3] = have_tp ? 0x3c : 0x10;

	/* Set WSNZ to 1 */
	buf[4] = 0x01;
	/*
	 * Set MAXIMUM COMPARE AND WRITE LENGTH
	 */
	if (dev->dev_attrib.emulate_caw)
		buf[5] = 0x01;

	/*
	 * Set OPTIMAL TRANSFER LENGTH GRANULARITY
	 */
	if (dev->transport->get_io_min && (min = dev->transport->get_io_min(dev)))
		put_unaligned_be16(min / dev->dev_attrib.block_size, &buf[6]);
	else
		put_unaligned_be16(1, &buf[6]);

	/*
	 * Set MAXIMUM TRANSFER LENGTH
	 *
	 * XXX: Currently assumes single PAGE_SIZE per scatterlist for fabrics
	 * enforcing maximum HW scatter-gather-list entry limit
	 */
	if (cmd->se_tfo->max_data_sg_nents) {
		mtl = (cmd->se_tfo->max_data_sg_nents * PAGE_SIZE) /
		       dev->dev_attrib.block_size;
	}
	put_unaligned_be32(min_not_zero(mtl, dev->dev_attrib.hw_max_sectors), &buf[8]);

	/*
	 * Set OPTIMAL TRANSFER LENGTH
	 */
	if (dev->transport->get_io_opt && (opt = dev->transport->get_io_opt(dev)))
		put_unaligned_be32(opt / dev->dev_attrib.block_size, &buf[12]);
	else
		put_unaligned_be32(dev->dev_attrib.optimal_sectors, &buf[12]);

	/*
	 * Exit now if we don't support TP.
	 */
	if (!have_tp)
		goto max_write_same;

	/*
	 * Set MAXIMUM UNMAP LBA COUNT
	 */
	put_unaligned_be32(dev->dev_attrib.max_unmap_lba_count, &buf[20]);

	/*
	 * Set MAXIMUM UNMAP BLOCK DESCRIPTOR COUNT
	 */
	put_unaligned_be32(dev->dev_attrib.max_unmap_block_desc_count,
			   &buf[24]);

	/*
	 * Set OPTIMAL UNMAP GRANULARITY
	 */
	put_unaligned_be32(dev->dev_attrib.unmap_granularity, &buf[28]);

	/*
	 * UNMAP GRANULARITY ALIGNMENT
	 */
	put_unaligned_be32(dev->dev_attrib.unmap_granularity_alignment,
			   &buf[32]);
	if (dev->dev_attrib.unmap_granularity_alignment != 0)
		buf[32] |= 0x80; /* Set the UGAVALID bit */

	/*
	 * MAXIMUM WRITE SAME LENGTH
	 */
max_write_same:
	put_unaligned_be64(dev->dev_attrib.max_write_same_len, &buf[36]);

	return 0;
}