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
struct ubi_vtbl_record {int dummy; } ;
struct ubi_device {int vtbl_slots; int /*<<< orphan*/  vtbl_size; } ;
struct ubi_attach_info {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ubi_vtbl_record* ERR_PTR (int) ; 
 int UBI_LAYOUT_VOLUME_EBS ; 
 int /*<<< orphan*/  UBI_VTBL_RECORD_SIZE ; 
 int create_vtbl (struct ubi_device*,struct ubi_attach_info*,int,struct ubi_vtbl_record*) ; 
 int /*<<< orphan*/  empty_vtbl_record ; 
 int /*<<< orphan*/  memcpy (struct ubi_vtbl_record*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (struct ubi_vtbl_record*) ; 
 struct ubi_vtbl_record* vzalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ubi_vtbl_record *create_empty_lvol(struct ubi_device *ubi,
						 struct ubi_attach_info *ai)
{
	int i;
	struct ubi_vtbl_record *vtbl;

	vtbl = vzalloc(ubi->vtbl_size);
	if (!vtbl)
		return ERR_PTR(-ENOMEM);

	for (i = 0; i < ubi->vtbl_slots; i++)
		memcpy(&vtbl[i], &empty_vtbl_record, UBI_VTBL_RECORD_SIZE);

	for (i = 0; i < UBI_LAYOUT_VOLUME_EBS; i++) {
		int err;

		err = create_vtbl(ubi, ai, i, vtbl);
		if (err) {
			vfree(vtbl);
			return ERR_PTR(err);
		}
	}

	return vtbl;
}