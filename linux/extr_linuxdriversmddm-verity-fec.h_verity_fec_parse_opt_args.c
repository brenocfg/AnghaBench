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
struct dm_verity {int dummy; } ;
struct dm_arg_set {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static inline int verity_fec_parse_opt_args(struct dm_arg_set *as,
					    struct dm_verity *v,
					    unsigned *argc,
					    const char *arg_name)
{
	return -EINVAL;
}