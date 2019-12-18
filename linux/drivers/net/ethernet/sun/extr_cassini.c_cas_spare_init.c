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
struct cas {int /*<<< orphan*/  rx_spare_lock; int /*<<< orphan*/  rx_spares_needed; int /*<<< orphan*/  rx_spare_list; int /*<<< orphan*/  rx_inuse_lock; int /*<<< orphan*/  rx_inuse_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RX_SPARE_COUNT ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cas_spare_init(struct cas *cp)
{
  	spin_lock(&cp->rx_inuse_lock);
	INIT_LIST_HEAD(&cp->rx_inuse_list);
	spin_unlock(&cp->rx_inuse_lock);

	spin_lock(&cp->rx_spare_lock);
	INIT_LIST_HEAD(&cp->rx_spare_list);
	cp->rx_spares_needed = RX_SPARE_COUNT;
	spin_unlock(&cp->rx_spare_lock);
}