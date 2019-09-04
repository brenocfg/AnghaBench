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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct kobj_attribute {scalar_t__ (* show ) (int /*<<< orphan*/ *,struct kobj_attribute*,char*) ;TYPE_1__ attr; } ;
struct cache_index_dir {int /*<<< orphan*/  kobj; struct cache* cache; } ;
struct cache {int /*<<< orphan*/  ofnode; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int ARRAY_SIZE (struct kobj_attribute**) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct kobj_attribute** cache_index_opt_attrs ; 
 char* cache_type_string (struct cache*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,...) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,struct kobj_attribute*,char*) ; 
 scalar_t__ sysfs_create_file (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void cacheinfo_create_index_opt_attrs(struct cache_index_dir *dir)
{
	const char *cache_type;
	struct cache *cache;
	char *buf;
	int i;

	buf = kmalloc(PAGE_SIZE, GFP_KERNEL);
	if (!buf)
		return;

	cache = dir->cache;
	cache_type = cache_type_string(cache);

	/* We don't want to create an attribute that can't provide a
	 * meaningful value.  Check the return value of each optional
	 * attribute's ->show method before registering the
	 * attribute.
	 */
	for (i = 0; i < ARRAY_SIZE(cache_index_opt_attrs); i++) {
		struct kobj_attribute *attr;
		ssize_t rc;

		attr = cache_index_opt_attrs[i];

		rc = attr->show(&dir->kobj, attr, buf);
		if (rc <= 0) {
			pr_debug("not creating %s attribute for "
				 "%pOF(%s) (rc = %zd)\n",
				 attr->attr.name, cache->ofnode,
				 cache_type, rc);
			continue;
		}
		if (sysfs_create_file(&dir->kobj, &attr->attr))
			pr_debug("could not create %s attribute for %pOF(%s)\n",
				 attr->attr.name, cache->ofnode, cache_type);
	}

	kfree(buf);
}