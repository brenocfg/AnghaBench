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
struct scaler_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCALER_TIMEOUT_CTRL ; 
 int /*<<< orphan*/  SCALER_TIMEOUT_CTRL_SET_TIMER_DIV (unsigned int) ; 
 int /*<<< orphan*/  SCALER_TIMEOUT_CTRL_SET_TIMER_VALUE (unsigned int) ; 
 int /*<<< orphan*/  SCALER_TIMEOUT_CTRL_TIMER_ENABLE ; 
 int /*<<< orphan*/  scaler_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void scaler_set_timer(struct scaler_context *scaler,
	unsigned int timer, unsigned int divider)
{
	u32 val;

	val = SCALER_TIMEOUT_CTRL_TIMER_ENABLE;
	val |= SCALER_TIMEOUT_CTRL_SET_TIMER_VALUE(timer);
	val |= SCALER_TIMEOUT_CTRL_SET_TIMER_DIV(divider);
	scaler_write(val, SCALER_TIMEOUT_CTRL);
}