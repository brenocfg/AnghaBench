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
struct xenbus_transaction {int dummy; } ;
struct blkfront_ring_info {int /*<<< orphan*/  evtchn; int /*<<< orphan*/ * ring_ref; struct blkfront_info* dev_info; } ;
struct blkfront_info {int nr_ring_pages; int /*<<< orphan*/  xbdev; } ;

/* Variables and functions */
 int RINGREF_NAME_LEN ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (int /*<<< orphan*/ ,int,char*,char const*) ; 
 int xenbus_printf (struct xenbus_transaction,char const*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_transaction_end (struct xenbus_transaction,int) ; 

__attribute__((used)) static int write_per_ring_nodes(struct xenbus_transaction xbt,
				struct blkfront_ring_info *rinfo, const char *dir)
{
	int err;
	unsigned int i;
	const char *message = NULL;
	struct blkfront_info *info = rinfo->dev_info;

	if (info->nr_ring_pages == 1) {
		err = xenbus_printf(xbt, dir, "ring-ref", "%u", rinfo->ring_ref[0]);
		if (err) {
			message = "writing ring-ref";
			goto abort_transaction;
		}
	} else {
		for (i = 0; i < info->nr_ring_pages; i++) {
			char ring_ref_name[RINGREF_NAME_LEN];

			snprintf(ring_ref_name, RINGREF_NAME_LEN, "ring-ref%u", i);
			err = xenbus_printf(xbt, dir, ring_ref_name,
					    "%u", rinfo->ring_ref[i]);
			if (err) {
				message = "writing ring-ref";
				goto abort_transaction;
			}
		}
	}

	err = xenbus_printf(xbt, dir, "event-channel", "%u", rinfo->evtchn);
	if (err) {
		message = "writing event-channel";
		goto abort_transaction;
	}

	return 0;

abort_transaction:
	xenbus_transaction_end(xbt, 1);
	if (message)
		xenbus_dev_fatal(info->xbdev, err, "%s", message);

	return err;
}