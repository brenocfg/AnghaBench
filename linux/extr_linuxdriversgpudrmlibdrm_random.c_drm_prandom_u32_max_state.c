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
typedef  int u64 ;
typedef  int u32 ;
struct rnd_state {int dummy; } ;

/* Variables and functions */
 scalar_t__ prandom_u32_state (struct rnd_state*) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static inline u32 drm_prandom_u32_max_state(u32 ep_ro, struct rnd_state *state)
{
	return upper_32_bits((u64)prandom_u32_state(state) * ep_ro);
}