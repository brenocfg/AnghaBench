#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u16 ;
struct TYPE_7__ {struct spi_mem_op* read_cache; } ;
struct spinand_device {void* oobbuf; void* databuf; int /*<<< orphan*/  spimem; TYPE_1__ op_templates; } ;
struct TYPE_8__ {void* in; } ;
struct TYPE_10__ {unsigned int nbytes; TYPE_2__ buf; } ;
struct TYPE_9__ {unsigned int val; } ;
struct spi_mem_op {TYPE_4__ data; TYPE_3__ addr; } ;
struct TYPE_12__ {void* in; } ;
struct TYPE_11__ {void* in; } ;
struct nand_page_io_req {unsigned int datalen; int dataoffs; unsigned int ooblen; scalar_t__ mode; scalar_t__ ooboffs; TYPE_6__ oobbuf; TYPE_5__ databuf; } ;
struct nand_device {int dummy; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ MTD_OPS_AUTO_OOB ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 
 int /*<<< orphan*/  mtd_ooblayout_get_databytes (struct mtd_info*,void*,void*,scalar_t__,unsigned int) ; 
 void* nanddev_page_size (struct nand_device*) ; 
 unsigned int nanddev_per_page_oobsize (struct nand_device*) ; 
 struct mtd_info* nanddev_to_mtd (struct nand_device*) ; 
 int spi_mem_adjust_op_size (int /*<<< orphan*/ ,struct spi_mem_op*) ; 
 int spi_mem_exec_op (int /*<<< orphan*/ ,struct spi_mem_op*) ; 
 int /*<<< orphan*/  spinand_cache_op_adjust_colum (struct spinand_device*,struct nand_page_io_req*,unsigned int*) ; 
 struct nand_device* spinand_to_nand (struct spinand_device*) ; 

__attribute__((used)) static int spinand_read_from_cache_op(struct spinand_device *spinand,
				      const struct nand_page_io_req *req)
{
	struct spi_mem_op op = *spinand->op_templates.read_cache;
	struct nand_device *nand = spinand_to_nand(spinand);
	struct mtd_info *mtd = nanddev_to_mtd(nand);
	struct nand_page_io_req adjreq = *req;
	unsigned int nbytes = 0;
	void *buf = NULL;
	u16 column = 0;
	int ret;

	if (req->datalen) {
		adjreq.datalen = nanddev_page_size(nand);
		adjreq.dataoffs = 0;
		adjreq.databuf.in = spinand->databuf;
		buf = spinand->databuf;
		nbytes = adjreq.datalen;
	}

	if (req->ooblen) {
		adjreq.ooblen = nanddev_per_page_oobsize(nand);
		adjreq.ooboffs = 0;
		adjreq.oobbuf.in = spinand->oobbuf;
		nbytes += nanddev_per_page_oobsize(nand);
		if (!buf) {
			buf = spinand->oobbuf;
			column = nanddev_page_size(nand);
		}
	}

	spinand_cache_op_adjust_colum(spinand, &adjreq, &column);
	op.addr.val = column;

	/*
	 * Some controllers are limited in term of max RX data size. In this
	 * case, just repeat the READ_CACHE operation after updating the
	 * column.
	 */
	while (nbytes) {
		op.data.buf.in = buf;
		op.data.nbytes = nbytes;
		ret = spi_mem_adjust_op_size(spinand->spimem, &op);
		if (ret)
			return ret;

		ret = spi_mem_exec_op(spinand->spimem, &op);
		if (ret)
			return ret;

		buf += op.data.nbytes;
		nbytes -= op.data.nbytes;
		op.addr.val += op.data.nbytes;
	}

	if (req->datalen)
		memcpy(req->databuf.in, spinand->databuf + req->dataoffs,
		       req->datalen);

	if (req->ooblen) {
		if (req->mode == MTD_OPS_AUTO_OOB)
			mtd_ooblayout_get_databytes(mtd, req->oobbuf.in,
						    spinand->oobbuf,
						    req->ooboffs,
						    req->ooblen);
		else
			memcpy(req->oobbuf.in, spinand->oobbuf + req->ooboffs,
			       req->ooblen);
	}

	return 0;
}