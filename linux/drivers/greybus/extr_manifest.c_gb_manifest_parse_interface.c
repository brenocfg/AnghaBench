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
struct manifest_desc {struct greybus_descriptor_interface* data; } ;
struct greybus_descriptor_interface {int /*<<< orphan*/  features; int /*<<< orphan*/  product_stringid; int /*<<< orphan*/  vendor_stringid; } ;
struct gb_interface {int /*<<< orphan*/  dev; int /*<<< orphan*/  features; struct gb_control* control; } ;
struct gb_control {char* vendor_string; char* product_string; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gb_manifest_parse_bundles (struct gb_interface*) ; 
 char* gb_string_get (struct gb_interface*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  release_manifest_descriptor (struct manifest_desc*) ; 

__attribute__((used)) static bool gb_manifest_parse_interface(struct gb_interface *intf,
					struct manifest_desc *interface_desc)
{
	struct greybus_descriptor_interface *desc_intf = interface_desc->data;
	struct gb_control *control = intf->control;
	char *str;

	/* Handle the strings first--they can fail */
	str = gb_string_get(intf, desc_intf->vendor_stringid);
	if (IS_ERR(str))
		return false;
	control->vendor_string = str;

	str = gb_string_get(intf, desc_intf->product_stringid);
	if (IS_ERR(str))
		goto out_free_vendor_string;
	control->product_string = str;

	/* Assign feature flags communicated via manifest */
	intf->features = desc_intf->features;

	/* Release the interface descriptor, now that we're done with it */
	release_manifest_descriptor(interface_desc);

	/* An interface must have at least one bundle descriptor */
	if (!gb_manifest_parse_bundles(intf)) {
		dev_err(&intf->dev, "manifest bundle descriptors not valid\n");
		goto out_err;
	}

	return true;
out_err:
	kfree(control->product_string);
	control->product_string = NULL;
out_free_vendor_string:
	kfree(control->vendor_string);
	control->vendor_string = NULL;

	return false;
}