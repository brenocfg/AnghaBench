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
struct asus_rfkill {int /*<<< orphan*/  control_id; int /*<<< orphan*/  asus; } ;

/* Variables and functions */
 int asus_pega_lucid_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pega_rfkill_set(void *data, bool blocked)
{
	struct asus_rfkill *rfk = data;

	int ret = asus_pega_lucid_set(rfk->asus, rfk->control_id, !blocked);
	return ret;
}