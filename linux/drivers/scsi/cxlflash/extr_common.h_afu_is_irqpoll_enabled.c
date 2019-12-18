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
struct afu {int /*<<< orphan*/  irqpoll_weight; } ;

/* Variables and functions */

__attribute__((used)) static inline bool afu_is_irqpoll_enabled(struct afu *afu)
{
	return !!afu->irqpoll_weight;
}