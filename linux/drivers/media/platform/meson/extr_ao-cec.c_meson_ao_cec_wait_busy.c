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
struct meson_ao_cec_device {scalar_t__ base; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int CEC_RW_BUS_BUSY ; 
 scalar_t__ CEC_RW_REG ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  ktime_add_us (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ktime_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static inline int meson_ao_cec_wait_busy(struct meson_ao_cec_device *ao_cec)
{
	ktime_t timeout = ktime_add_us(ktime_get(), 5000);

	while (readl_relaxed(ao_cec->base + CEC_RW_REG) & CEC_RW_BUS_BUSY) {
		if (ktime_compare(ktime_get(), timeout) > 0)
			return -ETIMEDOUT;
	}

	return 0;
}