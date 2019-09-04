#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct TYPE_6__ {TYPE_1__ version; } ;
struct TYPE_7__ {TYPE_2__ args; int /*<<< orphan*/  request; } ;
typedef  TYPE_3__ command ;
typedef  int /*<<< orphan*/  amb_dev ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  PRINTK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRB_GET_VERSION ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ command_do (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void amb_ucode_version(amb_dev *dev)
{
  u32 major;
  u32 minor;
  command cmd;
  cmd.request = cpu_to_be32 (SRB_GET_VERSION);
  while (command_do (dev, &cmd)) {
    set_current_state(TASK_UNINTERRUPTIBLE);
    schedule();
  }
  major = be32_to_cpu (cmd.args.version.major);
  minor = be32_to_cpu (cmd.args.version.minor);
  PRINTK (KERN_INFO, "microcode version is %u.%u", major, minor);
}