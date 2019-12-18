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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct fc_ct_hdr {int /*<<< orphan*/  ct_cmd; void* ct_fs_subtype; void* ct_fs_type; int /*<<< orphan*/  ct_rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_CT_REV ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
csio_fill_ct_iu(void *buf, uint8_t type, uint8_t sub_type, uint16_t op)
{
	struct fc_ct_hdr *cmd = (struct fc_ct_hdr *)buf;
	cmd->ct_rev = FC_CT_REV;
	cmd->ct_fs_type = type;
	cmd->ct_fs_subtype = sub_type;
	cmd->ct_cmd = htons(op);
}