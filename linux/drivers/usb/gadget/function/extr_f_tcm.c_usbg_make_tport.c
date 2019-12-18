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
typedef  int /*<<< orphan*/  u64 ;
struct se_wwn {int dummy; } ;
struct usbg_tport {struct se_wwn tport_wwn; int /*<<< orphan*/  tport_name; int /*<<< orphan*/  tport_wwpn; } ;
struct target_fabric_configfs {int dummy; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct se_wwn* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct usbg_tport* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 
 char* usbg_check_wwn (char const*) ; 

__attribute__((used)) static struct se_wwn *usbg_make_tport(
	struct target_fabric_configfs *tf,
	struct config_group *group,
	const char *name)
{
	struct usbg_tport *tport;
	const char *wnn_name;
	u64 wwpn = 0;

	wnn_name = usbg_check_wwn(name);
	if (!wnn_name)
		return ERR_PTR(-EINVAL);

	tport = kzalloc(sizeof(struct usbg_tport), GFP_KERNEL);
	if (!(tport))
		return ERR_PTR(-ENOMEM);

	tport->tport_wwpn = wwpn;
	snprintf(tport->tport_name, sizeof(tport->tport_name), "%s", wnn_name);
	return &tport->tport_wwn;
}