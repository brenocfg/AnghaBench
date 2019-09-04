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
struct dm_target {char* error; struct cache* private; } ;
struct cache_args {struct dm_target* ti; } ;
struct cache {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int cache_create (struct cache_args*,struct cache**) ; 
 int copy_ctr_args (struct cache*,unsigned int,char const**) ; 
 int /*<<< orphan*/  destroy (struct cache*) ; 
 int /*<<< orphan*/  destroy_cache_args (struct cache_args*) ; 
 struct cache_args* kzalloc (int,int /*<<< orphan*/ ) ; 
 int parse_cache_args (struct cache_args*,unsigned int,char**,char**) ; 

__attribute__((used)) static int cache_ctr(struct dm_target *ti, unsigned argc, char **argv)
{
	int r = -EINVAL;
	struct cache_args *ca;
	struct cache *cache = NULL;

	ca = kzalloc(sizeof(*ca), GFP_KERNEL);
	if (!ca) {
		ti->error = "Error allocating memory for cache";
		return -ENOMEM;
	}
	ca->ti = ti;

	r = parse_cache_args(ca, argc, argv, &ti->error);
	if (r)
		goto out;

	r = cache_create(ca, &cache);
	if (r)
		goto out;

	r = copy_ctr_args(cache, argc - 3, (const char **)argv + 3);
	if (r) {
		destroy(cache);
		goto out;
	}

	ti->private = cache;
out:
	destroy_cache_args(ca);
	return r;
}