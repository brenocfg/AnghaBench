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
struct its_vpe {int /*<<< orphan*/  vpt_page; int /*<<< orphan*/  vpe_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  its_free_pending_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_vpe_db_proxy_unmap (struct its_vpe*) ; 
 int /*<<< orphan*/  its_vpe_id_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void its_vpe_teardown(struct its_vpe *vpe)
{
	its_vpe_db_proxy_unmap(vpe);
	its_vpe_id_free(vpe->vpe_id);
	its_free_pending_table(vpe->vpt_page);
}