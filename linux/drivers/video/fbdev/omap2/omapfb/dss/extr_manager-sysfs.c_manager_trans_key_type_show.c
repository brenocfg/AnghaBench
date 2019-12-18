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
struct omap_overlay_manager_info {int trans_key_type; } ;
struct omap_overlay_manager {int /*<<< orphan*/  (* get_manager_info ) (struct omap_overlay_manager*,struct omap_overlay_manager_info*) ;} ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  enum omap_dss_trans_key_type { ____Placeholder_omap_dss_trans_key_type } omap_dss_trans_key_type ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub1 (struct omap_overlay_manager*,struct omap_overlay_manager_info*) ; 
 char** trans_key_type_str ; 

__attribute__((used)) static ssize_t manager_trans_key_type_show(struct omap_overlay_manager *mgr,
					   char *buf)
{
	enum omap_dss_trans_key_type key_type;
	struct omap_overlay_manager_info info;

	mgr->get_manager_info(mgr, &info);

	key_type = info.trans_key_type;
	BUG_ON(key_type >= ARRAY_SIZE(trans_key_type_str));

	return snprintf(buf, PAGE_SIZE, "%s\n", trans_key_type_str[key_type]);
}