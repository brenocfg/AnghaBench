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
struct edp_power_seq {int /*<<< orphan*/  t11_t12; int /*<<< orphan*/  t10; int /*<<< orphan*/  t9; int /*<<< orphan*/  t8; int /*<<< orphan*/  t1_t3; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
intel_pps_dump_state(const char *state_name, const struct edp_power_seq *seq)
{
	DRM_DEBUG_KMS("%s t1_t3 %d t8 %d t9 %d t10 %d t11_t12 %d\n",
		      state_name,
		      seq->t1_t3, seq->t8, seq->t9, seq->t10, seq->t11_t12);
}