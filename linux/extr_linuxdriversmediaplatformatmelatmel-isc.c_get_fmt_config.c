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
typedef  scalar_t__ u32 ;
struct fmt_config {scalar_t__ fourcc; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct fmt_config*) ; 
 struct fmt_config* fmt_configs_list ; 

__attribute__((used)) static struct fmt_config *get_fmt_config(u32 fourcc)
{
	struct fmt_config *config;
	int i;

	config = &fmt_configs_list[0];
	for (i = 0; i < ARRAY_SIZE(fmt_configs_list); i++) {
		if (config->fourcc == fourcc)
			return config;

		config++;
	}
	return NULL;
}