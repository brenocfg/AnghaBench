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
struct esas2r_adapter {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_BUSRST_DETECTED ; 
 int /*<<< orphan*/  AF_BUSRST_NEEDED ; 
 int /*<<< orphan*/  AF_CHPRST_DETECTED ; 
 int /*<<< orphan*/  AF_CHPRST_NEEDED ; 
 int /*<<< orphan*/  AF_PORT_CHANGE ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool esas2r_is_tasklet_pending(struct esas2r_adapter *a)
{

	return test_bit(AF_BUSRST_NEEDED, &a->flags) ||
	       test_bit(AF_BUSRST_DETECTED, &a->flags) ||
	       test_bit(AF_CHPRST_NEEDED, &a->flags) ||
	       test_bit(AF_CHPRST_DETECTED, &a->flags) ||
	       test_bit(AF_PORT_CHANGE, &a->flags);

}