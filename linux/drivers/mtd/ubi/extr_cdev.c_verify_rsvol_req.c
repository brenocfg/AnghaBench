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
struct ubi_rsvol_req {scalar_t__ bytes; scalar_t__ vol_id; } ;
struct ubi_device {scalar_t__ vtbl_slots; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int verify_rsvol_req(const struct ubi_device *ubi,
			    const struct ubi_rsvol_req *req)
{
	if (req->bytes <= 0)
		return -EINVAL;

	if (req->vol_id < 0 || req->vol_id >= ubi->vtbl_slots)
		return -EINVAL;

	return 0;
}