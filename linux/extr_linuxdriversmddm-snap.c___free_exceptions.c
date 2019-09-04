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
struct dm_snapshot {int /*<<< orphan*/  complete; int /*<<< orphan*/  pending; int /*<<< orphan*/ * kcopyd_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_exception_table_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_kcopyd_client_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exception_cache ; 
 int /*<<< orphan*/  pending_cache ; 

__attribute__((used)) static void __free_exceptions(struct dm_snapshot *s)
{
	dm_kcopyd_client_destroy(s->kcopyd_client);
	s->kcopyd_client = NULL;

	dm_exception_table_exit(&s->pending, pending_cache);
	dm_exception_table_exit(&s->complete, exception_cache);
}