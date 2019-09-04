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
struct drbd_request {struct drbd_device* device; } ;
struct drbd_device {int dummy; } ;
struct bio_and_error {scalar_t__ bio; } ;
typedef  enum drbd_req_event { ____Placeholder_drbd_req_event } drbd_req_event ;

/* Variables and functions */
 int __req_mod (struct drbd_request*,int,struct bio_and_error*) ; 
 int /*<<< orphan*/  complete_master_bio (struct drbd_device*,struct bio_and_error*) ; 

__attribute__((used)) static inline int _req_mod(struct drbd_request *req, enum drbd_req_event what)
{
	struct drbd_device *device = req->device;
	struct bio_and_error m;
	int rv;

	/* __req_mod possibly frees req, do not touch req after that! */
	rv = __req_mod(req, what, &m);
	if (m.bio)
		complete_master_bio(device, &m);

	return rv;
}