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
typedef  int uint32_t ;
struct mdp5_hw_mixer {int pp; } ;

/* Variables and functions */
 int MDP5_IRQ_PING_PONG_0_DONE ; 

__attribute__((used)) static inline uint32_t lm2ppdone(struct mdp5_hw_mixer *mixer)
{
	return MDP5_IRQ_PING_PONG_0_DONE << mixer->pp;
}