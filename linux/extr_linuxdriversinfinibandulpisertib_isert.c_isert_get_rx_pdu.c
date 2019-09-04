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
struct iscsi_conn {int dummy; } ;
struct completion {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_completion (struct completion*) ; 
 int /*<<< orphan*/  wait_for_completion_interruptible (struct completion*) ; 

__attribute__((used)) static void isert_get_rx_pdu(struct iscsi_conn *conn)
{
	struct completion comp;

	init_completion(&comp);

	wait_for_completion_interruptible(&comp);
}