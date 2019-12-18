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
struct var_t {int var_id; } ;
struct st_var_header {size_t var_id; int var_type; struct var_t* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  E_DEFAULT ; 
 int MAXVARS ; 
#define  VAR_NUM 130 
#define  VAR_STRING 129 
#define  VAR_TIME 128 
 int /*<<< orphan*/  spk_set_num_var (int /*<<< orphan*/ ,struct st_var_header*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spk_set_string_var (char*,struct st_var_header*,int /*<<< orphan*/ ) ; 
 struct st_var_header* var_headers ; 
 struct st_var_header** var_ptrs ; 

void speakup_register_var(struct var_t *var)
{
	static char nothing[2] = "\0";
	int i;
	struct st_var_header *p_header;

	BUG_ON(!var || var->var_id < 0 || var->var_id >= MAXVARS);
	if (!var_ptrs[0]) {
		for (i = 0; i < MAXVARS; i++) {
			p_header = &var_headers[i];
			var_ptrs[p_header->var_id] = p_header;
			p_header->data = NULL;
		}
	}
	p_header = var_ptrs[var->var_id];
	if (p_header->data)
		return;
	p_header->data = var;
	switch (p_header->var_type) {
	case VAR_STRING:
		spk_set_string_var(nothing, p_header, 0);
		break;
	case VAR_NUM:
	case VAR_TIME:
		spk_set_num_var(0, p_header, E_DEFAULT);
		break;
	default:
		break;
	}
}