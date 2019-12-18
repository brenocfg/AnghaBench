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
struct target_fabric_configfs {int dummy; } ;
struct se_wwn {int dummy; } ;
struct sbp_tport {struct se_wwn tport_wwn; int /*<<< orphan*/  tport_name; int /*<<< orphan*/  guid; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct se_wwn* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SBP_NAMELEN ; 
 struct sbp_tport* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbp_format_wwn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sbp_parse_wwn (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct se_wwn *sbp_make_tport(
		struct target_fabric_configfs *tf,
		struct config_group *group,
		const char *name)
{
	struct sbp_tport *tport;
	u64 guid = 0;

	if (sbp_parse_wwn(name, &guid) < 0)
		return ERR_PTR(-EINVAL);

	tport = kzalloc(sizeof(*tport), GFP_KERNEL);
	if (!tport)
		return ERR_PTR(-ENOMEM);

	tport->guid = guid;
	sbp_format_wwn(tport->tport_name, SBP_NAMELEN, guid);

	return &tport->tport_wwn;
}