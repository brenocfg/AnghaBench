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
struct se_node_acl {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  usbg_check_wwn (char const*) ; 

__attribute__((used)) static int usbg_init_nodeacl(struct se_node_acl *se_nacl, const char *name)
{
	if (!usbg_check_wwn(name))
		return -EINVAL;
	return 0;
}