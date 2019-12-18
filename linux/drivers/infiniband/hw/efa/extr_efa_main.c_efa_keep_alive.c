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
struct TYPE_2__ {int /*<<< orphan*/  keep_alive_rcvd; } ;
struct efa_dev {TYPE_1__ stats; } ;
struct efa_admin_aenq_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void efa_keep_alive(void *data, struct efa_admin_aenq_entry *aenq_e)
{
	struct efa_dev *dev = (struct efa_dev *)data;

	atomic64_inc(&dev->stats.keep_alive_rcvd);
}