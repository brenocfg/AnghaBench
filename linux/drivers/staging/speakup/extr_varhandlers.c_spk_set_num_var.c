#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int value; int low; int high; int default_val; int multiplier; char* synth_fmt; int* out_str; scalar_t__ offset; } ;
struct TYPE_5__ {TYPE_1__ n; } ;
struct var_t {TYPE_2__ u; } ;
struct st_var_header {int* p_val; scalar_t__ var_type; scalar_t__ var_id; struct var_t* data; } ;
struct TYPE_6__ {int (* synth_adjust ) (struct st_var_header*) ;} ;

/* Variables and functions */
 int ENODATA ; 
 int ERANGE ; 
#define  E_DEC 132 
#define  E_DEFAULT 131 
#define  E_INC 130 
#define  E_NEW_DEFAULT 129 
#define  E_SET 128 
 scalar_t__ FIRST_SYNTH_VAR ; 
 scalar_t__ PITCH ; 
 scalar_t__ PUNC_LEVEL ; 
 scalar_t__ VAR_TIME ; 
 int msecs_to_jiffies (int) ; 
 char* spk_pitch_buff ; 
 int /*<<< orphan*/  spk_punc_mask ; 
 int /*<<< orphan*/ * spk_punc_masks ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int stub1 (struct st_var_header*) ; 
 TYPE_3__* synth ; 
 int /*<<< orphan*/  synth_printf (char*,char*) ; 

int spk_set_num_var(int input, struct st_var_header *var, int how)
{
	int val;
	int *p_val = var->p_val;
	char buf[32];
	char *cp;
	struct var_t *var_data = var->data;

	if (!var_data)
		return -ENODATA;

	val = var_data->u.n.value;
	switch (how) {
	case E_NEW_DEFAULT:
		if (input < var_data->u.n.low || input > var_data->u.n.high)
			return -ERANGE;
		var_data->u.n.default_val = input;
		return 0;
	case E_DEFAULT:
		val = var_data->u.n.default_val;
		break;
	case E_SET:
		val = input;
		break;
	case E_INC:
		val += input;
		break;
	case E_DEC:
		val -= input;
		break;
	}

	if (val < var_data->u.n.low || val > var_data->u.n.high)
		return -ERANGE;

	var_data->u.n.value = val;
	if (var->var_type == VAR_TIME && p_val) {
		*p_val = msecs_to_jiffies(val);
		return 0;
	}
	if (p_val)
		*p_val = val;
	if (var->var_id == PUNC_LEVEL) {
		spk_punc_mask = spk_punc_masks[val];
		return 0;
	}
	if (var_data->u.n.multiplier != 0)
		val *= var_data->u.n.multiplier;
	val += var_data->u.n.offset;
	if (var->var_id < FIRST_SYNTH_VAR || !synth)
		return 0;
	if (synth->synth_adjust)
		return synth->synth_adjust(var);

	if (!var_data->u.n.synth_fmt)
		return 0;
	if (var->var_id == PITCH)
		cp = spk_pitch_buff;
	else
		cp = buf;
	if (!var_data->u.n.out_str)
		sprintf(cp, var_data->u.n.synth_fmt, (int)val);
	else
		sprintf(cp, var_data->u.n.synth_fmt,
			var_data->u.n.out_str[val]);
	synth_printf("%s", cp);
	return 0;
}