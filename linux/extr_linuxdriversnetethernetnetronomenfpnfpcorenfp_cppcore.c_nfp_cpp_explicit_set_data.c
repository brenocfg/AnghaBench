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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  data_ref; int /*<<< orphan*/  data_master; } ;
struct nfp_cpp_explicit {TYPE_1__ cmd; } ;

/* Variables and functions */

int nfp_cpp_explicit_set_data(struct nfp_cpp_explicit *expl,
			      u8 data_master, u16 data_ref)
{
	expl->cmd.data_master = data_master;
	expl->cmd.data_ref = data_ref;

	return 0;
}