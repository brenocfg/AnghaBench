#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  pv_pal_b_rev; int /*<<< orphan*/  pv_pal_b_model; int /*<<< orphan*/  pv_pal_a_rev; int /*<<< orphan*/  pv_pal_a_model; int /*<<< orphan*/  pv_pal_vendor; } ;
struct TYPE_6__ {TYPE_1__ pal_version_s; } ;
typedef  TYPE_2__ pal_version_u_t ;

/* Variables and functions */
 scalar_t__ ia64_pal_version (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int version_info(struct seq_file *m)
{
	pal_version_u_t min_ver, cur_ver;

	if (ia64_pal_version(&min_ver, &cur_ver) != 0)
		return 0;

	seq_printf(m,
		   "PAL_vendor : 0x%02x (min=0x%02x)\n"
		   "PAL_A      : %02x.%02x (min=%02x.%02x)\n"
		   "PAL_B      : %02x.%02x (min=%02x.%02x)\n",
		   cur_ver.pal_version_s.pv_pal_vendor,
		   min_ver.pal_version_s.pv_pal_vendor,
		   cur_ver.pal_version_s.pv_pal_a_model,
		   cur_ver.pal_version_s.pv_pal_a_rev,
		   min_ver.pal_version_s.pv_pal_a_model,
		   min_ver.pal_version_s.pv_pal_a_rev,
		   cur_ver.pal_version_s.pv_pal_b_model,
		   cur_ver.pal_version_s.pv_pal_b_rev,
		   min_ver.pal_version_s.pv_pal_b_model,
		   min_ver.pal_version_s.pv_pal_b_rev);
	return 0;
}