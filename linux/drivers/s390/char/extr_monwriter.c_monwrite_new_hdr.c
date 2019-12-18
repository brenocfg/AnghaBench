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
struct monwrite_hdr {int datalen; scalar_t__ mon_function; int hdrlen; } ;
struct mon_private {struct mon_buf* current_buf; int /*<<< orphan*/  list; struct monwrite_hdr hdr; } ;
struct mon_buf {int /*<<< orphan*/  list; struct monwrite_hdr hdr; struct mon_buf* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPLDATA_STOP_REC ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 scalar_t__ MONWRITE_GEN_EVENT ; 
 int MONWRITE_MAX_DATALEN ; 
 scalar_t__ MONWRITE_START_CONFIG ; 
 scalar_t__ MONWRITE_STOP_INTERVAL ; 
 int /*<<< orphan*/  kfree (struct mon_buf*) ; 
 void* kzalloc (int,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ mon_buf_count ; 
 scalar_t__ mon_max_bufs ; 
 int monwrite_diag (struct monwrite_hdr*,struct mon_buf*,int /*<<< orphan*/ ) ; 
 struct mon_buf* monwrite_find_hdr (struct mon_private*,struct monwrite_hdr*) ; 

__attribute__((used)) static int monwrite_new_hdr(struct mon_private *monpriv)
{
	struct monwrite_hdr *monhdr = &monpriv->hdr;
	struct mon_buf *monbuf;
	int rc = 0;

	if (monhdr->datalen > MONWRITE_MAX_DATALEN ||
	    monhdr->mon_function > MONWRITE_START_CONFIG ||
	    monhdr->hdrlen != sizeof(struct monwrite_hdr))
		return -EINVAL;
	monbuf = NULL;
	if (monhdr->mon_function != MONWRITE_GEN_EVENT)
		monbuf = monwrite_find_hdr(monpriv, monhdr);
	if (monbuf) {
		if (monhdr->mon_function == MONWRITE_STOP_INTERVAL) {
			monhdr->datalen = monbuf->hdr.datalen;
			rc = monwrite_diag(monhdr, monbuf->data,
					   APPLDATA_STOP_REC);
			list_del(&monbuf->list);
			mon_buf_count--;
			kfree(monbuf->data);
			kfree(monbuf);
			monbuf = NULL;
		}
	} else if (monhdr->mon_function != MONWRITE_STOP_INTERVAL) {
		if (mon_buf_count >= mon_max_bufs)
			return -ENOSPC;
		monbuf = kzalloc(sizeof(struct mon_buf), GFP_KERNEL);
		if (!monbuf)
			return -ENOMEM;
		monbuf->data = kzalloc(monhdr->datalen,
				       GFP_KERNEL | GFP_DMA);
		if (!monbuf->data) {
			kfree(monbuf);
			return -ENOMEM;
		}
		monbuf->hdr = *monhdr;
		list_add_tail(&monbuf->list, &monpriv->list);
		if (monhdr->mon_function != MONWRITE_GEN_EVENT)
			mon_buf_count++;
	}
	monpriv->current_buf = monbuf;
	return rc;
}