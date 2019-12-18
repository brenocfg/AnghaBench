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
struct monwrite_hdr {int mon_function; } ;
struct mon_private {struct mon_buf* current_buf; struct monwrite_hdr hdr; } ;
struct mon_buf {int diag_done; struct mon_buf* data; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPLDATA_GEN_EVENT_REC ; 
 int /*<<< orphan*/  APPLDATA_START_CONFIG_REC ; 
 int /*<<< orphan*/  APPLDATA_START_INTERVAL_REC ; 
 int /*<<< orphan*/  BUG () ; 
#define  MONWRITE_GEN_EVENT 130 
#define  MONWRITE_START_CONFIG 129 
#define  MONWRITE_START_INTERVAL 128 
 int /*<<< orphan*/  kfree (struct mon_buf*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int monwrite_diag (struct monwrite_hdr*,struct mon_buf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int monwrite_new_data(struct mon_private *monpriv)
{
	struct monwrite_hdr *monhdr = &monpriv->hdr;
	struct mon_buf *monbuf = monpriv->current_buf;
	int rc = 0;

	switch (monhdr->mon_function) {
	case MONWRITE_START_INTERVAL:
		if (!monbuf->diag_done) {
			rc = monwrite_diag(monhdr, monbuf->data,
					   APPLDATA_START_INTERVAL_REC);
			monbuf->diag_done = 1;
		}
		break;
	case MONWRITE_START_CONFIG:
		if (!monbuf->diag_done) {
			rc = monwrite_diag(monhdr, monbuf->data,
					   APPLDATA_START_CONFIG_REC);
			monbuf->diag_done = 1;
		}
		break;
	case MONWRITE_GEN_EVENT:
		rc = monwrite_diag(monhdr, monbuf->data,
				   APPLDATA_GEN_EVENT_REC);
		list_del(&monpriv->current_buf->list);
		kfree(monpriv->current_buf->data);
		kfree(monpriv->current_buf);
		monpriv->current_buf = NULL;
		break;
	default:
		/* monhdr->mon_function is checked in monwrite_new_hdr */
		BUG();
	}
	return rc;
}