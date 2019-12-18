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
struct st_var_header {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_DEFAULT ; 
 int /*<<< orphan*/  E_NEW_DEFAULT ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spk_set_num_var (int,struct st_var_header*,int /*<<< orphan*/ ) ; 
 struct st_var_header* spk_var_header_by_name (char*) ; 
 scalar_t__ synth ; 

__attribute__((used)) static inline void spk_reset_default_value(char *header_name,
					   int *synth_default_value, int idx)
{
	struct st_var_header *param;

	if (synth && synth_default_value) {
		param = spk_var_header_by_name(header_name);
		if (param)  {
			spk_set_num_var(synth_default_value[idx],
					param, E_NEW_DEFAULT);
			spk_set_num_var(0, param, E_DEFAULT);
			pr_info("%s reset to default value\n", param->name);
		}
	}
}