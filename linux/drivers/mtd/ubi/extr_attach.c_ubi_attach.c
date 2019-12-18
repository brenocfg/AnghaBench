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
struct ubi_device {int fm_disabled; int /*<<< orphan*/  vtbl; scalar_t__ fm; int /*<<< orphan*/  mean_ec; int /*<<< orphan*/  max_ec; int /*<<< orphan*/  corr_peb_count; scalar_t__ bad_peb_count; scalar_t__ peb_count; scalar_t__ good_peb_count; TYPE_1__* mtd; } ;
struct ubi_attach_info {int /*<<< orphan*/  max_sqnum; int /*<<< orphan*/  mean_ec; int /*<<< orphan*/  max_ec; int /*<<< orphan*/  corr_peb_count; scalar_t__ bad_peb_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int ENOMEM ; 
 int UBI_FM_MAX_START ; 
 int UBI_NO_FASTMAP ; 
 struct ubi_attach_info* alloc_ai () ; 
 int /*<<< orphan*/  dbg_gen (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_ai (struct ubi_attach_info*) ; 
 scalar_t__ mtd_div_by_eb (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ mtd_is_eccerr (int) ; 
 int scan_all (struct ubi_device*,struct ubi_attach_info*,int) ; 
 int scan_fast (struct ubi_device*,struct ubi_attach_info**) ; 
 int self_check_eba (struct ubi_device*,struct ubi_attach_info*,struct ubi_attach_info*) ; 
 scalar_t__ ubi_dbg_chk_fastmap (struct ubi_device*) ; 
 int ubi_eba_init (struct ubi_device*,struct ubi_attach_info*) ; 
 int /*<<< orphan*/  ubi_free_internal_volumes (struct ubi_device*) ; 
 int ubi_read_volume_table (struct ubi_device*,struct ubi_attach_info*) ; 
 int /*<<< orphan*/  ubi_wl_close (struct ubi_device*) ; 
 int ubi_wl_init (struct ubi_device*,struct ubi_attach_info*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

int ubi_attach(struct ubi_device *ubi, int force_scan)
{
	int err;
	struct ubi_attach_info *ai;

	ai = alloc_ai();
	if (!ai)
		return -ENOMEM;

#ifdef CONFIG_MTD_UBI_FASTMAP
	/* On small flash devices we disable fastmap in any case. */
	if ((int)mtd_div_by_eb(ubi->mtd->size, ubi->mtd) <= UBI_FM_MAX_START) {
		ubi->fm_disabled = 1;
		force_scan = 1;
	}

	if (force_scan)
		err = scan_all(ubi, ai, 0);
	else {
		err = scan_fast(ubi, &ai);
		if (err > 0 || mtd_is_eccerr(err)) {
			if (err != UBI_NO_FASTMAP) {
				destroy_ai(ai);
				ai = alloc_ai();
				if (!ai)
					return -ENOMEM;

				err = scan_all(ubi, ai, 0);
			} else {
				err = scan_all(ubi, ai, UBI_FM_MAX_START);
			}
		}
	}
#else
	err = scan_all(ubi, ai, 0);
#endif
	if (err)
		goto out_ai;

	ubi->bad_peb_count = ai->bad_peb_count;
	ubi->good_peb_count = ubi->peb_count - ubi->bad_peb_count;
	ubi->corr_peb_count = ai->corr_peb_count;
	ubi->max_ec = ai->max_ec;
	ubi->mean_ec = ai->mean_ec;
	dbg_gen("max. sequence number:       %llu", ai->max_sqnum);

	err = ubi_read_volume_table(ubi, ai);
	if (err)
		goto out_ai;

	err = ubi_wl_init(ubi, ai);
	if (err)
		goto out_vtbl;

	err = ubi_eba_init(ubi, ai);
	if (err)
		goto out_wl;

#ifdef CONFIG_MTD_UBI_FASTMAP
	if (ubi->fm && ubi_dbg_chk_fastmap(ubi)) {
		struct ubi_attach_info *scan_ai;

		scan_ai = alloc_ai();
		if (!scan_ai) {
			err = -ENOMEM;
			goto out_wl;
		}

		err = scan_all(ubi, scan_ai, 0);
		if (err) {
			destroy_ai(scan_ai);
			goto out_wl;
		}

		err = self_check_eba(ubi, ai, scan_ai);
		destroy_ai(scan_ai);

		if (err)
			goto out_wl;
	}
#endif

	destroy_ai(ai);
	return 0;

out_wl:
	ubi_wl_close(ubi);
out_vtbl:
	ubi_free_internal_volumes(ubi);
	vfree(ubi->vtbl);
out_ai:
	destroy_ai(ai);
	return err;
}