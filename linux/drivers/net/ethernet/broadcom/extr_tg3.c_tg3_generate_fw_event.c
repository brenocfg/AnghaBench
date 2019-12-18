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
typedef  int /*<<< orphan*/  u32 ;
struct tg3 {int /*<<< orphan*/  last_event_jiffies; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRC_RX_CPU_DRIVER_EVENT ; 
 int /*<<< orphan*/  GRC_RX_CPU_EVENT ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  tr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32_f (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void tg3_generate_fw_event(struct tg3 *tp)
{
	u32 val;

	val = tr32(GRC_RX_CPU_EVENT);
	val |= GRC_RX_CPU_DRIVER_EVENT;
	tw32_f(GRC_RX_CPU_EVENT, val);

	tp->last_event_jiffies = jiffies;
}