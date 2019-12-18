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
struct chsc_ssd_info {int path_mask; int fla_valid_mask; int* fla; int /*<<< orphan*/ * chpid; } ;
struct chp_link {int fla_mask; int fla; int /*<<< orphan*/  chpid; } ;

/* Variables and functions */
 int /*<<< orphan*/  chp_id_is_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int chp_ssd_get_mask(struct chsc_ssd_info *ssd, struct chp_link *link)
{
	int i;
	int mask;

	for (i = 0; i < 8; i++) {
		mask = 0x80 >> i;
		if (!(ssd->path_mask & mask))
			continue;
		if (!chp_id_is_equal(&ssd->chpid[i], &link->chpid))
			continue;
		if ((ssd->fla_valid_mask & mask) &&
		    ((ssd->fla[i] & link->fla_mask) != link->fla))
			continue;
		return mask;
	}
	return 0;
}