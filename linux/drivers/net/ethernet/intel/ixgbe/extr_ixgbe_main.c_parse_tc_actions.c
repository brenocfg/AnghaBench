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
struct tcf_exts {int dummy; } ;
struct ixgbe_adapter {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int parse_tc_actions(struct ixgbe_adapter *adapter,
			    struct tcf_exts *exts, u64 *action, u8 *queue)
{
	return -EINVAL;
}