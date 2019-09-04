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
struct dm_cache_policy {int (* emit_config_values ) (struct dm_cache_policy*,char*,unsigned int,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMEMIT (char*) ; 
 int stub1 (struct dm_cache_policy*,char*,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int policy_emit_config_values(struct dm_cache_policy *p, char *result,
					    unsigned maxlen, ssize_t *sz_ptr)
{
	ssize_t sz = *sz_ptr;
	if (p->emit_config_values)
		return p->emit_config_values(p, result, maxlen, sz_ptr);

	DMEMIT("0 ");
	*sz_ptr = sz;
	return 0;
}