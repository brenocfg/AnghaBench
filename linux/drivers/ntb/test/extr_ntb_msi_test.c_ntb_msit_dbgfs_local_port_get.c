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
typedef  int /*<<< orphan*/  u64 ;
struct ntb_msit_ctx {int /*<<< orphan*/  ntb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ntb_port_number (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ntb_msit_dbgfs_local_port_get(void *data, u64 *port)
{
	struct ntb_msit_ctx *nm = data;

	*port = ntb_port_number(nm->ntb);

	return 0;
}