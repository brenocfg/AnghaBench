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
struct dm_target {struct cache* private; } ;
struct cache {int dummy; } ;

/* Variables and functions */
 scalar_t__ CM_READ_ONLY ; 
 int /*<<< orphan*/  DMERR (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  cache_device_name (struct cache*) ; 
 scalar_t__ get_cache_mode (struct cache*) ; 
 int process_invalidate_cblocks_message (struct cache*,unsigned int,char const**) ; 
 int set_config_value (struct cache*,char*,char*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 

__attribute__((used)) static int cache_message(struct dm_target *ti, unsigned argc, char **argv,
			 char *result, unsigned maxlen)
{
	struct cache *cache = ti->private;

	if (!argc)
		return -EINVAL;

	if (get_cache_mode(cache) >= CM_READ_ONLY) {
		DMERR("%s: unable to service cache target messages in READ_ONLY or FAIL mode",
		      cache_device_name(cache));
		return -EOPNOTSUPP;
	}

	if (!strcasecmp(argv[0], "invalidate_cblocks"))
		return process_invalidate_cblocks_message(cache, argc - 1, (const char **) argv + 1);

	if (argc != 2)
		return -EINVAL;

	return set_config_value(cache, argv[0], argv[1]);
}