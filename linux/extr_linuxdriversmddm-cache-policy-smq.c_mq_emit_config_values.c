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
struct dm_cache_policy {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMEMIT (char*) ; 

__attribute__((used)) static int mq_emit_config_values(struct dm_cache_policy *p, char *result,
				 unsigned maxlen, ssize_t *sz_ptr)
{
	ssize_t sz = *sz_ptr;

	DMEMIT("10 random_threshold 0 "
	       "sequential_threshold 0 "
	       "discard_promote_adjustment 0 "
	       "read_promote_adjustment 0 "
	       "write_promote_adjustment 0 ");

	*sz_ptr = sz;
	return 0;
}