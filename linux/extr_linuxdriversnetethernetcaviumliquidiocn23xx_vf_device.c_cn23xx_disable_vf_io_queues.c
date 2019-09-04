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
struct octeon_device {scalar_t__ num_iqs; scalar_t__ num_oqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  cn23xx_vf_reset_io_queues (struct octeon_device*,scalar_t__) ; 

__attribute__((used)) static void cn23xx_disable_vf_io_queues(struct octeon_device *oct)
{
	u32 num_queues = oct->num_iqs;

	/* per HRM, rings can only be disabled via reset operation,
	 * NOT via SLI_PKT()_INPUT/OUTPUT_CONTROL[ENB]
	 */
	if (num_queues < oct->num_oqs)
		num_queues = oct->num_oqs;

	cn23xx_vf_reset_io_queues(oct, num_queues);
}