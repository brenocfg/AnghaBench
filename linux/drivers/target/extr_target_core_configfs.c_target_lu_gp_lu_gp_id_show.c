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
struct t10_alua_lu_gp {int /*<<< orphan*/  lu_gp_id; int /*<<< orphan*/  lu_gp_valid_id; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 struct t10_alua_lu_gp* to_lu_gp (struct config_item*) ; 

__attribute__((used)) static ssize_t target_lu_gp_lu_gp_id_show(struct config_item *item, char *page)
{
	struct t10_alua_lu_gp *lu_gp = to_lu_gp(item);

	if (!lu_gp->lu_gp_valid_id)
		return 0;
	return sprintf(page, "%hu\n", lu_gp->lu_gp_id);
}