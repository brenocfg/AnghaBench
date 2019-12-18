#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int len; int /*<<< orphan*/  cmd; } ;
struct TYPE_3__ {void* vlan_id; void* vlan_valid; int /*<<< orphan*/  rgid; TYPE_2__ hdr; } ;
union ism_query_rgid {TYPE_1__ request; } ;
typedef  int /*<<< orphan*/  u64 ;
typedef  void* u32 ;
struct smcd_dev {struct ism_dev* priv; } ;
struct ism_dev {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  ISM_QUERY_RGID ; 
 int ism_cmd (struct ism_dev*,union ism_query_rgid*) ; 
 int /*<<< orphan*/  memset (union ism_query_rgid*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ism_query_rgid(struct smcd_dev *smcd, u64 rgid, u32 vid_valid,
			  u32 vid)
{
	struct ism_dev *ism = smcd->priv;
	union ism_query_rgid cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.request.hdr.cmd = ISM_QUERY_RGID;
	cmd.request.hdr.len = sizeof(cmd.request);

	cmd.request.rgid = rgid;
	cmd.request.vlan_valid = vid_valid;
	cmd.request.vlan_id = vid;

	return ism_cmd(ism, &cmd);
}