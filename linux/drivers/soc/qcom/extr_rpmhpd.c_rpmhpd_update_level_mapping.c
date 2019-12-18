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
typedef  scalar_t__ u16 ;
struct rpmhpd {int level_count; scalar_t__* level; int /*<<< orphan*/  res_name; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (scalar_t__ const*) ; 
 int PTR_ERR (scalar_t__ const*) ; 
 int RPMH_ARC_MAX_LEVELS ; 
 scalar_t__* cmd_db_read_aux_data (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,scalar_t__) ; 

__attribute__((used)) static int rpmhpd_update_level_mapping(struct rpmhpd *rpmhpd)
{
	int i;
	const u16 *buf;

	buf = cmd_db_read_aux_data(rpmhpd->res_name, &rpmhpd->level_count);
	if (IS_ERR(buf))
		return PTR_ERR(buf);

	/* 2 bytes used for each command DB aux data entry */
	rpmhpd->level_count >>= 1;

	if (rpmhpd->level_count > RPMH_ARC_MAX_LEVELS)
		return -EINVAL;

	for (i = 0; i < rpmhpd->level_count; i++) {
		rpmhpd->level[i] = buf[i];

		/*
		 * The AUX data may be zero padded.  These 0 valued entries at
		 * the end of the map must be ignored.
		 */
		if (i > 0 && rpmhpd->level[i] == 0) {
			rpmhpd->level_count = i;
			break;
		}
		pr_debug("%s: ARC hlvl=%2d --> vlvl=%4u\n", rpmhpd->res_name, i,
			 rpmhpd->level[i]);
	}

	return 0;
}