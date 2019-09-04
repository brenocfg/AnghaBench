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
struct drbd_device {int dummy; } ;
struct bio {int /*<<< orphan*/  bi_status; int /*<<< orphan*/  bi_disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  __release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 int /*<<< orphan*/  drbd_err (struct drbd_device*,char*) ; 
 scalar_t__ drbd_insert_fault (struct drbd_device*,int) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 int /*<<< orphan*/  local ; 

__attribute__((used)) static inline void drbd_generic_make_request(struct drbd_device *device,
					     int fault_type, struct bio *bio)
{
	__release(local);
	if (!bio->bi_disk) {
		drbd_err(device, "drbd_generic_make_request: bio->bi_disk == NULL\n");
		bio->bi_status = BLK_STS_IOERR;
		bio_endio(bio);
		return;
	}

	if (drbd_insert_fault(device, fault_type))
		bio_io_error(bio);
	else
		generic_make_request(bio);
}