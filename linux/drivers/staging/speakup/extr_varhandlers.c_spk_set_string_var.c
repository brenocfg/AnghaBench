#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ default_val; } ;
struct TYPE_3__ {TYPE_2__ s; } ;
struct var_t {TYPE_1__ u; } ;
struct st_var_header {scalar_t__ p_val; struct var_t* data; } ;

/* Variables and functions */
 int E2BIG ; 
 int ENODATA ; 
 int ERESTART ; 
 int MAXVARLEN ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

int spk_set_string_var(const char *page, struct st_var_header *var, int len)
{
	struct var_t *var_data = var->data;

	if (!var_data)
		return -ENODATA;
	if (len > MAXVARLEN)
		return -E2BIG;
	if (!len) {
		if (!var_data->u.s.default_val)
			return 0;
		if (!var->p_val)
			var->p_val = var_data->u.s.default_val;
		if (var->p_val != var_data->u.s.default_val)
			strcpy((char *)var->p_val, var_data->u.s.default_val);
		return -ERESTART;
	} else if (var->p_val) {
		strcpy((char *)var->p_val, page);
	} else {
		return -E2BIG;
	}
	return 0;
}