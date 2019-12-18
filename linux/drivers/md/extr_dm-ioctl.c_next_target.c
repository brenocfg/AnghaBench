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
typedef  int uint32_t ;
struct dm_target_spec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int invalid_str (char*,void*) ; 

__attribute__((used)) static int next_target(struct dm_target_spec *last, uint32_t next, void *end,
		       struct dm_target_spec **spec, char **target_params)
{
	*spec = (struct dm_target_spec *) ((unsigned char *) last + next);
	*target_params = (char *) (*spec + 1);

	if (*spec < (last + 1))
		return -EINVAL;

	return invalid_str(*target_params, end);
}