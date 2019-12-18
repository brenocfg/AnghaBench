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
struct mlxsw_afk_element_usage {int dummy; } ;
struct mlxsw_sp_acl_tcam_vgroup {int patterns_count; struct mlxsw_sp_acl_tcam_pattern* patterns; struct mlxsw_afk_element_usage tmplt_elusage; scalar_t__ tmplt_elusage_set; } ;
struct mlxsw_sp_acl_tcam_pattern {int /*<<< orphan*/  elements_count; int /*<<< orphan*/  elements; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  memcpy (struct mlxsw_afk_element_usage*,struct mlxsw_afk_element_usage*,int) ; 
 int /*<<< orphan*/  mlxsw_afk_element_usage_fill (struct mlxsw_afk_element_usage*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mlxsw_afk_element_usage_subset (struct mlxsw_afk_element_usage*,struct mlxsw_afk_element_usage*) ; 

__attribute__((used)) static void
mlxsw_sp_acl_tcam_vgroup_use_patterns(struct mlxsw_sp_acl_tcam_vgroup *vgroup,
				      struct mlxsw_afk_element_usage *elusage,
				      struct mlxsw_afk_element_usage *out)
{
	const struct mlxsw_sp_acl_tcam_pattern *pattern;
	int i;

	/* In case the template is set, we don't have to look up the pattern
	 * and just use the template.
	 */
	if (vgroup->tmplt_elusage_set) {
		memcpy(out, &vgroup->tmplt_elusage, sizeof(*out));
		WARN_ON(!mlxsw_afk_element_usage_subset(elusage, out));
		return;
	}

	for (i = 0; i < vgroup->patterns_count; i++) {
		pattern = &vgroup->patterns[i];
		mlxsw_afk_element_usage_fill(out, pattern->elements,
					     pattern->elements_count);
		if (mlxsw_afk_element_usage_subset(elusage, out))
			return;
	}
	memcpy(out, elusage, sizeof(*out));
}