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
typedef  int /*<<< orphan*/  u32 ;
struct drm_dp_dpcd_ident {int /*<<< orphan*/  oui; } ;
struct dpcd_quirk {int is_branch; int /*<<< orphan*/  quirks; int /*<<< orphan*/  oui; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct dpcd_quirk*) ; 
 struct dpcd_quirk* dpcd_quirk_list ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32
drm_dp_get_quirks(const struct drm_dp_dpcd_ident *ident, bool is_branch)
{
	const struct dpcd_quirk *quirk;
	u32 quirks = 0;
	int i;

	for (i = 0; i < ARRAY_SIZE(dpcd_quirk_list); i++) {
		quirk = &dpcd_quirk_list[i];

		if (quirk->is_branch != is_branch)
			continue;

		if (memcmp(quirk->oui, ident->oui, sizeof(ident->oui)) != 0)
			continue;

		quirks |= quirk->quirks;
	}

	return quirks;
}