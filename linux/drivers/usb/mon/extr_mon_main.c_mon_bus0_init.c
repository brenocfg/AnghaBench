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
struct mon_bus {int /*<<< orphan*/  bin_inited; int /*<<< orphan*/  text_inited; int /*<<< orphan*/  r_list; int /*<<< orphan*/  lock; int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mon_bin_add (struct mon_bus*,int /*<<< orphan*/ *) ; 
 struct mon_bus mon_bus0 ; 
 int /*<<< orphan*/  mon_text_add (struct mon_bus*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mon_bus0_init(void)
{
	struct mon_bus *mbus = &mon_bus0;

	kref_init(&mbus->ref);
	spin_lock_init(&mbus->lock);
	INIT_LIST_HEAD(&mbus->r_list);

	mbus->text_inited = mon_text_add(mbus, NULL);
	mbus->bin_inited = mon_bin_add(mbus, NULL);
}