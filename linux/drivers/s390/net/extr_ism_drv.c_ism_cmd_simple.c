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
struct TYPE_3__ {int len; int /*<<< orphan*/  cmd; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;
union ism_cmd_simple {TYPE_2__ request; } ;
typedef  int /*<<< orphan*/  u32 ;
struct ism_dev {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int ism_cmd (struct ism_dev*,union ism_cmd_simple*) ; 
 int /*<<< orphan*/  memset (union ism_cmd_simple*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ism_cmd_simple(struct ism_dev *ism, u32 cmd_code)
{
	union ism_cmd_simple cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.request.hdr.cmd = cmd_code;
	cmd.request.hdr.len = sizeof(cmd.request);

	return ism_cmd(ism, &cmd);
}