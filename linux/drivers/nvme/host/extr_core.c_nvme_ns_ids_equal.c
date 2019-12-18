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
struct nvme_ns_ids {int /*<<< orphan*/  eui64; int /*<<< orphan*/  nguid; int /*<<< orphan*/  uuid; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ uuid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool nvme_ns_ids_equal(struct nvme_ns_ids *a, struct nvme_ns_ids *b)
{
	return uuid_equal(&a->uuid, &b->uuid) &&
		memcmp(&a->nguid, &b->nguid, sizeof(a->nguid)) == 0 &&
		memcmp(&a->eui64, &b->eui64, sizeof(a->eui64)) == 0;
}