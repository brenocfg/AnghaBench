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
typedef  scalar_t__ uint32_t ;
struct scsi_cmnd {int dummy; } ;
struct scatterlist {scalar_t__ length; scalar_t__ offset; } ;
struct csio_dma_buf {scalar_t__ len; void* vaddr; } ;
struct csio_ioreq {struct csio_dma_buf gen_list; } ;
struct csio_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ DID_ERROR ; 
 scalar_t__ DID_OK ; 
 scalar_t__ PAGE_MASK ; 
 scalar_t__ PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  csio_dbg (struct csio_hw*,char*,void*,scalar_t__,void*,scalar_t__) ; 
 int /*<<< orphan*/  csio_err (struct csio_hw*,char*,struct scatterlist*,struct csio_ioreq*) ; 
 scalar_t__ csio_list_next (struct csio_dma_buf*) ; 
 scalar_t__ csio_scsi_cmnd (struct csio_ioreq*) ; 
 void* kmap_atomic (scalar_t__) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 scalar_t__ scsi_bufflen (struct scsi_cmnd*) ; 
 struct scatterlist* scsi_sglist (struct scsi_cmnd*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 scalar_t__ sg_page (struct scatterlist*) ; 

__attribute__((used)) static inline uint32_t
csio_scsi_copy_to_sgl(struct csio_hw *hw, struct csio_ioreq *req)
{
	struct scsi_cmnd *scmnd  = (struct scsi_cmnd *)csio_scsi_cmnd(req);
	struct scatterlist *sg;
	uint32_t bytes_left;
	uint32_t bytes_copy;
	uint32_t buf_off = 0;
	uint32_t start_off = 0;
	uint32_t sg_off = 0;
	void *sg_addr;
	void *buf_addr;
	struct csio_dma_buf *dma_buf;

	bytes_left = scsi_bufflen(scmnd);
	sg = scsi_sglist(scmnd);
	dma_buf = (struct csio_dma_buf *)csio_list_next(&req->gen_list);

	/* Copy data from driver buffer to SGs of SCSI CMD */
	while (bytes_left > 0 && sg && dma_buf) {
		if (buf_off >= dma_buf->len) {
			buf_off = 0;
			dma_buf = (struct csio_dma_buf *)
					csio_list_next(dma_buf);
			continue;
		}

		if (start_off >= sg->length) {
			start_off -= sg->length;
			sg = sg_next(sg);
			continue;
		}

		buf_addr = dma_buf->vaddr + buf_off;
		sg_off = sg->offset + start_off;
		bytes_copy = min((dma_buf->len - buf_off),
				sg->length - start_off);
		bytes_copy = min((uint32_t)(PAGE_SIZE - (sg_off & ~PAGE_MASK)),
				 bytes_copy);

		sg_addr = kmap_atomic(sg_page(sg) + (sg_off >> PAGE_SHIFT));
		if (!sg_addr) {
			csio_err(hw, "failed to kmap sg:%p of ioreq:%p\n",
				sg, req);
			break;
		}

		csio_dbg(hw, "copy_to_sgl:sg_addr %p sg_off %d buf %p len %d\n",
				sg_addr, sg_off, buf_addr, bytes_copy);
		memcpy(sg_addr + (sg_off & ~PAGE_MASK), buf_addr, bytes_copy);
		kunmap_atomic(sg_addr);

		start_off +=  bytes_copy;
		buf_off += bytes_copy;
		bytes_left -= bytes_copy;
	}

	if (bytes_left > 0)
		return DID_ERROR;
	else
		return DID_OK;
}