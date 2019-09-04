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
struct xvtc_device {int /*<<< orphan*/  xvip; } ;

/* Variables and functions */
 scalar_t__ XVTC_GENERATOR_OFFSET ; 
 int /*<<< orphan*/  xvip_write (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void xvtc_gen_write(struct xvtc_device *xvtc, u32 addr, u32 value)
{
	xvip_write(&xvtc->xvip, XVTC_GENERATOR_OFFSET + addr, value);
}