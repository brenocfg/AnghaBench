#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ response_expected; } ;
struct TYPE_8__ {TYPE_3__ flags; } ;
struct TYPE_5__ {int features; } ;
struct TYPE_6__ {TYPE_1__ init_chipset; } ;
struct controlvm_message {TYPE_4__ hdr; TYPE_2__ cmd; } ;
typedef  enum visor_chipset_feature { ____Placeholder_visor_chipset_feature } visor_chipset_feature ;

/* Variables and functions */
 int CONTROLVM_RESP_ALREADY_DONE ; 
 int CONTROLVM_RESP_SUCCESS ; 
 int EIO ; 
 int VISOR_CHIPSET_FEATURE_PARA_HOTPLUG ; 
 int VISOR_CHIPSET_FEATURE_REPLY ; 
 int controlvm_respond_chipset_init (TYPE_4__*,int,int) ; 

__attribute__((used)) static int chipset_init(struct controlvm_message *inmsg)
{
	static int chipset_inited;
	enum visor_chipset_feature features = 0;
	int rc = CONTROLVM_RESP_SUCCESS;
	int res = 0;

	if (chipset_inited) {
		rc = -CONTROLVM_RESP_ALREADY_DONE;
		res = -EIO;
		goto out_respond;
	}
	chipset_inited = 1;
	/*
	 * Set features to indicate we support parahotplug (if Command also
	 * supports it). Set the "reply" bit so Command knows this is a
	 * features-aware driver.
	 */
	features = inmsg->cmd.init_chipset.features &
		   VISOR_CHIPSET_FEATURE_PARA_HOTPLUG;
	features |= VISOR_CHIPSET_FEATURE_REPLY;

out_respond:
	if (inmsg->hdr.flags.response_expected)
		res = controlvm_respond_chipset_init(&inmsg->hdr, rc, features);

	return res;
}