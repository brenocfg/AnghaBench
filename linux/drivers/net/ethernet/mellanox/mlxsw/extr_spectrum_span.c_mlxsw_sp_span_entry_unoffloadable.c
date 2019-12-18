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
struct mlxsw_sp_span_parms {int /*<<< orphan*/ * dest_port; } ;

/* Variables and functions */

__attribute__((used)) static int
mlxsw_sp_span_entry_unoffloadable(struct mlxsw_sp_span_parms *sparmsp)
{
	sparmsp->dest_port = NULL;
	return 0;
}