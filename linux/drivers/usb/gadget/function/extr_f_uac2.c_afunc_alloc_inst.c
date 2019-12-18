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
struct usb_function_instance {int /*<<< orphan*/  group; int /*<<< orphan*/  free_func_inst; } ;
struct f_uac2_opts {struct usb_function_instance func_inst; int /*<<< orphan*/  req_number; int /*<<< orphan*/  c_ssize; int /*<<< orphan*/  c_srate; int /*<<< orphan*/  c_chmask; int /*<<< orphan*/  p_ssize; int /*<<< orphan*/  p_srate; int /*<<< orphan*/  p_chmask; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct usb_function_instance* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  UAC2_DEF_CCHMASK ; 
 int /*<<< orphan*/  UAC2_DEF_CSRATE ; 
 int /*<<< orphan*/  UAC2_DEF_CSSIZE ; 
 int /*<<< orphan*/  UAC2_DEF_PCHMASK ; 
 int /*<<< orphan*/  UAC2_DEF_PSRATE ; 
 int /*<<< orphan*/  UAC2_DEF_PSSIZE ; 
 int /*<<< orphan*/  UAC2_DEF_REQ_NUM ; 
 int /*<<< orphan*/  afunc_free_inst ; 
 int /*<<< orphan*/  config_group_init_type_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f_uac2_func_type ; 
 struct f_uac2_opts* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct usb_function_instance *afunc_alloc_inst(void)
{
	struct f_uac2_opts *opts;

	opts = kzalloc(sizeof(*opts), GFP_KERNEL);
	if (!opts)
		return ERR_PTR(-ENOMEM);

	mutex_init(&opts->lock);
	opts->func_inst.free_func_inst = afunc_free_inst;

	config_group_init_type_name(&opts->func_inst.group, "",
				    &f_uac2_func_type);

	opts->p_chmask = UAC2_DEF_PCHMASK;
	opts->p_srate = UAC2_DEF_PSRATE;
	opts->p_ssize = UAC2_DEF_PSSIZE;
	opts->c_chmask = UAC2_DEF_CCHMASK;
	opts->c_srate = UAC2_DEF_CSRATE;
	opts->c_ssize = UAC2_DEF_CSSIZE;
	opts->req_number = UAC2_DEF_REQ_NUM;
	return &opts->func_inst;
}