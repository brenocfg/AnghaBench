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
struct gsm_mux {unsigned int num; } ;

/* Variables and functions */
 unsigned int NUM_DLCI ; 

__attribute__((used)) static inline unsigned int mux_num_to_base(struct gsm_mux *gsm)
{
	return gsm->num * NUM_DLCI;
}