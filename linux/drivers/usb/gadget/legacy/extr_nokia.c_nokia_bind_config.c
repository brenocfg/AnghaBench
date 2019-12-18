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
struct usb_function {int dummy; } ;
struct usb_configuration {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct usb_function*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct usb_function*) ; 
 int PTR_ERR (struct usb_function*) ; 
 struct usb_function* f_acm_cfg1 ; 
 struct usb_function* f_acm_cfg2 ; 
 struct usb_function* f_ecm_cfg1 ; 
 struct usb_function* f_ecm_cfg2 ; 
 struct usb_function* f_msg_cfg1 ; 
 struct usb_function* f_msg_cfg2 ; 
 struct usb_function* f_obex1_cfg1 ; 
 struct usb_function* f_obex1_cfg2 ; 
 struct usb_function* f_obex2_cfg1 ; 
 struct usb_function* f_obex2_cfg2 ; 
 struct usb_function* f_phonet_cfg1 ; 
 struct usb_function* f_phonet_cfg2 ; 
 struct usb_function* fi_acm ; 
 struct usb_function* fi_ecm ; 
 struct usb_function* fi_msg ; 
 struct usb_function* fi_obex1 ; 
 struct usb_function* fi_obex2 ; 
 struct usb_function* fi_phonet ; 
 struct usb_configuration nokia_config_500ma_driver ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int usb_add_function (struct usb_configuration*,struct usb_function*) ; 
 struct usb_function* usb_get_function (struct usb_function*) ; 
 int /*<<< orphan*/  usb_put_function (struct usb_function*) ; 
 int /*<<< orphan*/  usb_remove_function (struct usb_configuration*,struct usb_function*) ; 

__attribute__((used)) static int nokia_bind_config(struct usb_configuration *c)
{
	struct usb_function *f_acm;
	struct usb_function *f_phonet = NULL;
	struct usb_function *f_obex1 = NULL;
	struct usb_function *f_ecm;
	struct usb_function *f_obex2 = NULL;
	struct usb_function *f_msg;
	int status = 0;
	int obex1_stat = -1;
	int obex2_stat = -1;
	int phonet_stat = -1;

	if (!IS_ERR(fi_phonet)) {
		f_phonet = usb_get_function(fi_phonet);
		if (IS_ERR(f_phonet))
			pr_debug("could not get phonet function\n");
	}

	if (!IS_ERR(fi_obex1)) {
		f_obex1 = usb_get_function(fi_obex1);
		if (IS_ERR(f_obex1))
			pr_debug("could not get obex function 0\n");
	}

	if (!IS_ERR(fi_obex2)) {
		f_obex2 = usb_get_function(fi_obex2);
		if (IS_ERR(f_obex2))
			pr_debug("could not get obex function 1\n");
	}

	f_acm = usb_get_function(fi_acm);
	if (IS_ERR(f_acm)) {
		status = PTR_ERR(f_acm);
		goto err_get_acm;
	}

	f_ecm = usb_get_function(fi_ecm);
	if (IS_ERR(f_ecm)) {
		status = PTR_ERR(f_ecm);
		goto err_get_ecm;
	}

	f_msg = usb_get_function(fi_msg);
	if (IS_ERR(f_msg)) {
		status = PTR_ERR(f_msg);
		goto err_get_msg;
	}

	if (!IS_ERR_OR_NULL(f_phonet)) {
		phonet_stat = usb_add_function(c, f_phonet);
		if (phonet_stat)
			pr_debug("could not add phonet function\n");
	}

	if (!IS_ERR_OR_NULL(f_obex1)) {
		obex1_stat = usb_add_function(c, f_obex1);
		if (obex1_stat)
			pr_debug("could not add obex function 0\n");
	}

	if (!IS_ERR_OR_NULL(f_obex2)) {
		obex2_stat = usb_add_function(c, f_obex2);
		if (obex2_stat)
			pr_debug("could not add obex function 1\n");
	}

	status = usb_add_function(c, f_acm);
	if (status)
		goto err_conf;

	status = usb_add_function(c, f_ecm);
	if (status) {
		pr_debug("could not bind ecm config %d\n", status);
		goto err_ecm;
	}

	status = usb_add_function(c, f_msg);
	if (status)
		goto err_msg;

	if (c == &nokia_config_500ma_driver) {
		f_acm_cfg1 = f_acm;
		f_ecm_cfg1 = f_ecm;
		f_phonet_cfg1 = f_phonet;
		f_obex1_cfg1 = f_obex1;
		f_obex2_cfg1 = f_obex2;
		f_msg_cfg1 = f_msg;
	} else {
		f_acm_cfg2 = f_acm;
		f_ecm_cfg2 = f_ecm;
		f_phonet_cfg2 = f_phonet;
		f_obex1_cfg2 = f_obex1;
		f_obex2_cfg2 = f_obex2;
		f_msg_cfg2 = f_msg;
	}

	return status;
err_msg:
	usb_remove_function(c, f_ecm);
err_ecm:
	usb_remove_function(c, f_acm);
err_conf:
	if (!obex2_stat)
		usb_remove_function(c, f_obex2);
	if (!obex1_stat)
		usb_remove_function(c, f_obex1);
	if (!phonet_stat)
		usb_remove_function(c, f_phonet);
	usb_put_function(f_msg);
err_get_msg:
	usb_put_function(f_ecm);
err_get_ecm:
	usb_put_function(f_acm);
err_get_acm:
	if (!IS_ERR_OR_NULL(f_obex2))
		usb_put_function(f_obex2);
	if (!IS_ERR_OR_NULL(f_obex1))
		usb_put_function(f_obex1);
	if (!IS_ERR_OR_NULL(f_phonet))
		usb_put_function(f_phonet);
	return status;
}