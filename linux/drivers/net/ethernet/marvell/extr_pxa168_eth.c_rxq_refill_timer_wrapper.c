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
struct pxa168_eth_private {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 struct pxa168_eth_private* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct pxa168_eth_private* pep ; 
 int /*<<< orphan*/  timeout ; 

__attribute__((used)) static inline void rxq_refill_timer_wrapper(struct timer_list *t)
{
	struct pxa168_eth_private *pep = from_timer(pep, t, timeout);
	napi_schedule(&pep->napi);
}