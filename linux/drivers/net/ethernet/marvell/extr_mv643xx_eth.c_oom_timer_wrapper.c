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
struct timer_list {int dummy; } ;
struct mv643xx_eth_private {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 struct mv643xx_eth_private* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct mv643xx_eth_private* mp ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rx_oom ; 

__attribute__((used)) static inline void oom_timer_wrapper(struct timer_list *t)
{
	struct mv643xx_eth_private *mp = from_timer(mp, t, rx_oom);

	napi_schedule(&mp->napi);
}