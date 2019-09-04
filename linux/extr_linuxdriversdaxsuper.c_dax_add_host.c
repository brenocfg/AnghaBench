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
struct dax_device {char const* host; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int dax_host_hash (char const*) ; 
 int /*<<< orphan*/ * dax_host_list ; 
 int /*<<< orphan*/  dax_host_lock ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dax_add_host(struct dax_device *dax_dev, const char *host)
{
	int hash;

	/*
	 * Unconditionally init dax_dev since it's coming from a
	 * non-zeroed slab cache
	 */
	INIT_HLIST_NODE(&dax_dev->list);
	dax_dev->host = host;
	if (!host)
		return;

	hash = dax_host_hash(host);
	spin_lock(&dax_host_lock);
	hlist_add_head(&dax_dev->list, &dax_host_list[hash]);
	spin_unlock(&dax_host_lock);
}