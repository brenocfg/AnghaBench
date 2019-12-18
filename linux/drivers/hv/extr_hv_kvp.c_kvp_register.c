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
struct TYPE_6__ {int operation; } ;
struct TYPE_4__ {char* version; } ;
struct TYPE_5__ {TYPE_1__ kvp_register; } ;
struct hv_kvp_msg {TYPE_3__ kvp_hdr; TYPE_2__ body; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HV_DRV_VERSION ; 
 int /*<<< orphan*/  hvt ; 
 int /*<<< orphan*/  hvutil_transport_send (int /*<<< orphan*/ ,struct hv_kvp_msg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hv_kvp_msg*) ; 
 int /*<<< orphan*/  kvp_register_done ; 
 struct hv_kvp_msg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kvp_register(int reg_value)
{

	struct hv_kvp_msg *kvp_msg;
	char *version;

	kvp_msg = kzalloc(sizeof(*kvp_msg), GFP_KERNEL);

	if (kvp_msg) {
		version = kvp_msg->body.kvp_register.version;
		kvp_msg->kvp_hdr.operation = reg_value;
		strcpy(version, HV_DRV_VERSION);

		hvutil_transport_send(hvt, kvp_msg, sizeof(*kvp_msg),
				      kvp_register_done);
		kfree(kvp_msg);
	}
}