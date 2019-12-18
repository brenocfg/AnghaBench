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
struct ubi_volume_desc {int mode; struct ubi_volume* vol; } ;
struct ubi_volume {int readers; int writers; int metaonly; int exclusive; TYPE_1__* ubi; } ;
struct TYPE_2__ {int /*<<< orphan*/  volumes_lock; } ;

/* Variables and functions */
 int UBI_EXCLUSIVE ; 
 int UBI_METAONLY ; 
 int UBI_READONLY ; 
 int UBI_READWRITE ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 

__attribute__((used)) static void revoke_exclusive(struct ubi_volume_desc *desc, int mode)
{
	struct ubi_volume *vol = desc->vol;

	spin_lock(&vol->ubi->volumes_lock);
	ubi_assert(vol->readers == 0 && vol->writers == 0 && vol->metaonly == 0);
	ubi_assert(vol->exclusive == 1 && desc->mode == UBI_EXCLUSIVE);
	vol->exclusive = 0;
	if (mode == UBI_READONLY)
		vol->readers = 1;
	else if (mode == UBI_READWRITE)
		vol->writers = 1;
	else if (mode == UBI_METAONLY)
		vol->metaonly = 1;
	else
		vol->exclusive = 1;
	spin_unlock(&vol->ubi->volumes_lock);

	desc->mode = mode;
}