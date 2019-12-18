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
typedef  int u8 ;

/* Variables and functions */
 int RATE_MASK ; 
 int TX_RATE_11M ; 
 int TX_RATE_1M ; 
 int TX_RATE_2M ; 
 int TX_RATE_5M ; 

__attribute__((used)) static inline bool is_11b_rate(u8 rate)
{
	return (((rate & RATE_MASK) == TX_RATE_1M) ||
		((rate & RATE_MASK) == TX_RATE_2M) ||
		((rate & RATE_MASK) == TX_RATE_5M) ||
		((rate & RATE_MASK) == TX_RATE_11M));
}