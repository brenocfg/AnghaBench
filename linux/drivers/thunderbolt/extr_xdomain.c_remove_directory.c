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
struct tb_property_dir {int dummy; } ;
struct TYPE_2__ {struct tb_property_dir const* dir; } ;
struct tb_property {TYPE_1__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  TB_PROPERTY_TYPE_DIRECTORY ; 
 struct tb_property* tb_property_find (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_property_remove (struct tb_property*) ; 
 int /*<<< orphan*/  xdomain_property_dir ; 

__attribute__((used)) static bool remove_directory(const char *key, const struct tb_property_dir *dir)
{
	struct tb_property *p;

	p = tb_property_find(xdomain_property_dir, key,
			     TB_PROPERTY_TYPE_DIRECTORY);
	if (p && p->value.dir == dir) {
		tb_property_remove(p);
		return true;
	}
	return false;
}