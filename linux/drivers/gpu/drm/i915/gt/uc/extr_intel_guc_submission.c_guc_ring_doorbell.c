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
typedef  scalar_t__ u32 ;
struct intel_guc_client {int /*<<< orphan*/  wq_lock; } ;
struct guc_doorbell_info {scalar_t__ db_status; int /*<<< orphan*/  cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ GUC_DOORBELL_ENABLED ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct guc_doorbell_info* __get_doorbell (struct intel_guc_client*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 scalar_t__ xchg (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void guc_ring_doorbell(struct intel_guc_client *client)
{
	struct guc_doorbell_info *db;
	u32 cookie;

	lockdep_assert_held(&client->wq_lock);

	/* pointer of current doorbell cacheline */
	db = __get_doorbell(client);

	/*
	 * We're not expecting the doorbell cookie to change behind our back,
	 * we also need to treat 0 as a reserved value.
	 */
	cookie = READ_ONCE(db->cookie);
	WARN_ON_ONCE(xchg(&db->cookie, cookie + 1 ?: cookie + 2) != cookie);

	/* XXX: doorbell was lost and need to acquire it again */
	GEM_BUG_ON(db->db_status != GUC_DOORBELL_ENABLED);
}