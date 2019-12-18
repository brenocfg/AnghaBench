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
struct esas2r_adapter {int /*<<< orphan*/  flags; TYPE_1__* nvram; } ;
struct TYPE_2__ {int options2; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_CHPRST_PENDING ; 
 int /*<<< orphan*/  AF_DEGRADED_MODE ; 
 int /*<<< orphan*/  AF_HEARTBEAT_ENB ; 
 int SASNVR2_HEARTBEAT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void esas2r_enable_heartbeat(struct esas2r_adapter *a)
{
	if (!test_bit(AF_DEGRADED_MODE, &a->flags) &&
	    !test_bit(AF_CHPRST_PENDING, &a->flags) &&
	    (a->nvram->options2 & SASNVR2_HEARTBEAT))
		set_bit(AF_HEARTBEAT_ENB, &a->flags);
	else
		clear_bit(AF_HEARTBEAT_ENB, &a->flags);
}