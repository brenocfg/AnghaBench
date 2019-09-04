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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct sockaddr_storage {int dummy; } ;
struct se_node_acl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int inet_pton_with_scope (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,struct sockaddr_storage*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int srpt_parse_guid (int /*<<< orphan*/ *,char const*) ; 
 int srpt_parse_i_port_id (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int srpt_init_nodeacl(struct se_node_acl *se_nacl, const char *name)
{
	struct sockaddr_storage sa;
	u64 guid;
	u8 i_port_id[16];
	int ret;

	ret = srpt_parse_guid(&guid, name);
	if (ret < 0)
		ret = srpt_parse_i_port_id(i_port_id, name);
	if (ret < 0)
		ret = inet_pton_with_scope(&init_net, AF_UNSPEC, name, NULL,
					   &sa);
	if (ret < 0)
		pr_err("invalid initiator port ID %s\n", name);
	return ret;
}