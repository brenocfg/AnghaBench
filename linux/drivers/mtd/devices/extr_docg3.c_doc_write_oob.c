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
typedef  int /*<<< orphan*/  u8 ;
struct mtd_oob_ops {size_t len; size_t ooblen; int mode; scalar_t__ retlen; scalar_t__ oobretlen; int /*<<< orphan*/  ooboffs; int /*<<< orphan*/ * datbuf; int /*<<< orphan*/ * oobbuf; } ;
struct mtd_info {int oobsize; int oobavail; struct docg3* priv; } ;
struct docg3 {size_t oob_write_ofs; TYPE_1__* cascade; int /*<<< orphan*/ * oob_write_buf; } ;
typedef  int /*<<< orphan*/  oob ;
typedef  size_t loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int DOC_LAYOUT_OOB_SIZE ; 
 size_t DOC_LAYOUT_PAGE_SIZE ; 
 int EINVAL ; 
#define  MTD_OPS_AUTO_OOB 130 
#define  MTD_OPS_PLACE_OOB 129 
#define  MTD_OPS_RAW 128 
 int doc_backup_oob (struct docg3*,size_t,struct mtd_oob_ops*) ; 
 int /*<<< orphan*/  doc_dbg (char*,size_t,int,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  doc_fill_autooob (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int doc_guess_autoecc (struct mtd_oob_ops*) ; 
 int /*<<< orphan*/  doc_set_device_id (struct docg3*,int /*<<< orphan*/ ) ; 
 int doc_write_page (struct docg3*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int doc_write_oob(struct mtd_info *mtd, loff_t ofs,
			 struct mtd_oob_ops *ops)
{
	struct docg3 *docg3 = mtd->priv;
	int ret, autoecc, oobdelta;
	u8 *oobbuf = ops->oobbuf;
	u8 *buf = ops->datbuf;
	size_t len, ooblen;
	u8 oob[DOC_LAYOUT_OOB_SIZE];

	if (buf)
		len = ops->len;
	else
		len = 0;
	if (oobbuf)
		ooblen = ops->ooblen;
	else
		ooblen = 0;

	if (oobbuf && ops->mode == MTD_OPS_PLACE_OOB)
		oobbuf += ops->ooboffs;

	doc_dbg("doc_write_oob(from=%lld, mode=%d, data=(%p:%zu), oob=(%p:%zu))\n",
		ofs, ops->mode, buf, len, oobbuf, ooblen);
	switch (ops->mode) {
	case MTD_OPS_PLACE_OOB:
	case MTD_OPS_RAW:
		oobdelta = mtd->oobsize;
		break;
	case MTD_OPS_AUTO_OOB:
		oobdelta = mtd->oobavail;
		break;
	default:
		return -EINVAL;
	}
	if ((len % DOC_LAYOUT_PAGE_SIZE) || (ooblen % oobdelta) ||
	    (ofs % DOC_LAYOUT_PAGE_SIZE))
		return -EINVAL;
	if (len && ooblen &&
	    (len / DOC_LAYOUT_PAGE_SIZE) != (ooblen / oobdelta))
		return -EINVAL;

	ops->oobretlen = 0;
	ops->retlen = 0;
	ret = 0;
	if (len == 0 && ooblen == 0)
		return -EINVAL;
	if (len == 0 && ooblen > 0)
		return doc_backup_oob(docg3, ofs, ops);

	autoecc = doc_guess_autoecc(ops);
	if (autoecc < 0)
		return autoecc;

	mutex_lock(&docg3->cascade->lock);
	while (!ret && len > 0) {
		memset(oob, 0, sizeof(oob));
		if (ofs == docg3->oob_write_ofs)
			memcpy(oob, docg3->oob_write_buf, DOC_LAYOUT_OOB_SIZE);
		else if (ooblen > 0 && ops->mode == MTD_OPS_AUTO_OOB)
			doc_fill_autooob(oob, oobbuf);
		else if (ooblen > 0)
			memcpy(oob, oobbuf, DOC_LAYOUT_OOB_SIZE);
		ret = doc_write_page(docg3, ofs, buf, oob, autoecc);

		ofs += DOC_LAYOUT_PAGE_SIZE;
		len -= DOC_LAYOUT_PAGE_SIZE;
		buf += DOC_LAYOUT_PAGE_SIZE;
		if (ooblen) {
			oobbuf += oobdelta;
			ooblen -= oobdelta;
			ops->oobretlen += oobdelta;
		}
		ops->retlen += DOC_LAYOUT_PAGE_SIZE;
	}

	doc_set_device_id(docg3, 0);
	mutex_unlock(&docg3->cascade->lock);
	return ret;
}