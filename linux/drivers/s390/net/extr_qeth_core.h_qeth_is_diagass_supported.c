#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int diagass_support; } ;
struct qeth_card {TYPE_1__ info; } ;
typedef  enum qeth_diags_cmds { ____Placeholder_qeth_diags_cmds } qeth_diags_cmds ;
typedef  int __u32 ;

/* Variables and functions */

__attribute__((used)) static inline int qeth_is_diagass_supported(struct qeth_card *card,
		enum qeth_diags_cmds cmd)
{
	return card->info.diagass_support & (__u32)cmd;
}