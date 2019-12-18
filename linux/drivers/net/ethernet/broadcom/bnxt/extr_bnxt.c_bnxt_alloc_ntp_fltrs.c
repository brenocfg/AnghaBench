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
struct bnxt {int flags; int /*<<< orphan*/  ntp_fltr_bmap; scalar_t__ ntp_fltr_count; int /*<<< orphan*/ * ntp_fltr_hash_tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int BNXT_FLAG_RFS ; 
 int BNXT_NTP_FLTR_HASH_SIZE ; 
 int /*<<< orphan*/  BNXT_NTP_FLTR_MAX_FLTR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_alloc_ntp_fltrs(struct bnxt *bp)
{
#ifdef CONFIG_RFS_ACCEL
	int i, rc = 0;

	if (!(bp->flags & BNXT_FLAG_RFS))
		return 0;

	for (i = 0; i < BNXT_NTP_FLTR_HASH_SIZE; i++)
		INIT_HLIST_HEAD(&bp->ntp_fltr_hash_tbl[i]);

	bp->ntp_fltr_count = 0;
	bp->ntp_fltr_bmap = kcalloc(BITS_TO_LONGS(BNXT_NTP_FLTR_MAX_FLTR),
				    sizeof(long),
				    GFP_KERNEL);

	if (!bp->ntp_fltr_bmap)
		rc = -ENOMEM;

	return rc;
#else
	return 0;
#endif
}