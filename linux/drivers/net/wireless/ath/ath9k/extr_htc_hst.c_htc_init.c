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
struct htc_target {int dummy; } ;

/* Variables and functions */
 int htc_config_pipe_credits (struct htc_target*) ; 
 int htc_setup_complete (struct htc_target*) ; 

int htc_init(struct htc_target *target)
{
	int ret;

	ret = htc_config_pipe_credits(target);
	if (ret)
		return ret;

	return htc_setup_complete(target);
}