#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  housekeeping; int /*<<< orphan*/  unassigned_cell_count; int /*<<< orphan*/  hec_error_count; int /*<<< orphan*/  rx_cell_count; int /*<<< orphan*/  tx_cell_count; } ;
typedef  TYPE_1__ hrz_dev ;

/* Variables and functions */
 int /*<<< orphan*/  HEC_ERROR_COUNT_OFF ; 
 int HZ ; 
 int /*<<< orphan*/  RX_CELL_COUNT_OFF ; 
 int /*<<< orphan*/  TX_CELL_COUNT_OFF ; 
 int /*<<< orphan*/  UNASSIGNED_CELL_COUNT_OFF ; 
 TYPE_1__* dev ; 
 TYPE_1__* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  housekeeping ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ rd_regw (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_housekeeping (struct timer_list *t) {
  // just stats at the moment
  hrz_dev * dev = from_timer(dev, t, housekeeping);

  // collect device-specific (not driver/atm-linux) stats here
  dev->tx_cell_count += rd_regw (dev, TX_CELL_COUNT_OFF);
  dev->rx_cell_count += rd_regw (dev, RX_CELL_COUNT_OFF);
  dev->hec_error_count += rd_regw (dev, HEC_ERROR_COUNT_OFF);
  dev->unassigned_cell_count += rd_regw (dev, UNASSIGNED_CELL_COUNT_OFF);

  mod_timer (&dev->housekeeping, jiffies + HZ/10);

  return;
}