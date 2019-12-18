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
struct dpu_encoder_phys {int /*<<< orphan*/  pending_kickoff_cnt; int /*<<< orphan*/  pending_ctlstart_cnt; } ;

/* Variables and functions */
 int atomic_inc_return (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int dpu_encoder_phys_inc_pending(struct dpu_encoder_phys *phys)
{
	atomic_inc_return(&phys->pending_ctlstart_cnt);
	return atomic_inc_return(&phys->pending_kickoff_cnt);
}