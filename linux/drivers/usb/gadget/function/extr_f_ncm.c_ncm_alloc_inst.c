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
struct usb_os_desc {int /*<<< orphan*/  ext_prop; int /*<<< orphan*/  ext_compat_id; } ;
struct usb_function_instance {int /*<<< orphan*/  group; int /*<<< orphan*/  (* free_func_inst ) (struct usb_function_instance*) ;} ;
struct net_device {int dummy; } ;
struct f_ncm_opts {struct usb_function_instance func_inst; struct net_device* ncm_interf_group; struct usb_os_desc ncm_os_desc; struct net_device* net; int /*<<< orphan*/  lock; int /*<<< orphan*/  ncm_ext_compat_id; } ;
typedef  struct net_device config_group ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct usb_function_instance* ERR_CAST (struct net_device*) ; 
 struct usb_function_instance* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct net_device*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  config_group_init_type_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 struct net_device* gether_setup_default () ; 
 int /*<<< orphan*/  kfree (struct f_ncm_opts*) ; 
 struct f_ncm_opts* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ncm_free_inst (struct usb_function_instance*) ; 
 int /*<<< orphan*/  ncm_func_type ; 
 struct net_device* usb_os_desc_prepare_interf_dir (int /*<<< orphan*/ *,int,struct usb_os_desc**,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct usb_function_instance *ncm_alloc_inst(void)
{
	struct f_ncm_opts *opts;
	struct usb_os_desc *descs[1];
	char *names[1];
	struct config_group *ncm_interf_group;

	opts = kzalloc(sizeof(*opts), GFP_KERNEL);
	if (!opts)
		return ERR_PTR(-ENOMEM);
	opts->ncm_os_desc.ext_compat_id = opts->ncm_ext_compat_id;

	mutex_init(&opts->lock);
	opts->func_inst.free_func_inst = ncm_free_inst;
	opts->net = gether_setup_default();
	if (IS_ERR(opts->net)) {
		struct net_device *net = opts->net;
		kfree(opts);
		return ERR_CAST(net);
	}
	INIT_LIST_HEAD(&opts->ncm_os_desc.ext_prop);

	descs[0] = &opts->ncm_os_desc;
	names[0] = "ncm";

	config_group_init_type_name(&opts->func_inst.group, "", &ncm_func_type);
	ncm_interf_group =
		usb_os_desc_prepare_interf_dir(&opts->func_inst.group, 1, descs,
					       names, THIS_MODULE);
	if (IS_ERR(ncm_interf_group)) {
		ncm_free_inst(&opts->func_inst);
		return ERR_CAST(ncm_interf_group);
	}
	opts->ncm_interf_group = ncm_interf_group;

	return &opts->func_inst;
}