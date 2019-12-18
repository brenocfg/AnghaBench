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
struct raw3270 {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ RAW3270_STATE_INIT ; 
 scalar_t__ RAW3270_STATE_READY ; 

__attribute__((used)) static inline int raw3270_state_final(struct raw3270 *rp)
{
	return rp->state == RAW3270_STATE_INIT ||
		rp->state == RAW3270_STATE_READY;
}