#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u32 ;
struct qedi_boot_target {int ipv6_en; int /*<<< orphan*/  ip_addr; int /*<<< orphan*/  iscsi_name; } ;
struct TYPE_6__ {int ctrl_flags; } ;
struct nvm_iscsi_block {TYPE_5__* target; TYPE_1__ generic; } ;
struct TYPE_9__ {char* byte; } ;
struct TYPE_8__ {char* byte; } ;
struct TYPE_7__ {char* byte; } ;
struct TYPE_10__ {TYPE_4__ ipv4_addr; TYPE_3__ ipv6_addr; TYPE_2__ target_name; } ;

/* Variables and functions */
 int IPV4_LEN ; 
 int IPV6_LEN ; 
 int NVM_ISCSI_CFG_GEN_IPV6_ENABLED ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 

__attribute__((used)) static void qedi_get_boot_tgt_info(struct nvm_iscsi_block *block,
				   struct qedi_boot_target *tgt, u8 index)
{
	u32 ipv6_en;

	ipv6_en = !!(block->generic.ctrl_flags &
		     NVM_ISCSI_CFG_GEN_IPV6_ENABLED);

	snprintf(tgt->iscsi_name, sizeof(tgt->iscsi_name), "%s\n",
		 block->target[index].target_name.byte);

	tgt->ipv6_en = ipv6_en;

	if (ipv6_en)
		snprintf(tgt->ip_addr, IPV6_LEN, "%pI6\n",
			 block->target[index].ipv6_addr.byte);
	else
		snprintf(tgt->ip_addr, IPV4_LEN, "%pI4\n",
			 block->target[index].ipv4_addr.byte);
}