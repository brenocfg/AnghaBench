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

/* Variables and functions */
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 

__attribute__((used)) static inline int sms_to_status(u32 is_demod_locked, u32 is_rf_locked)
{
	if (is_demod_locked)
		return FE_HAS_SIGNAL  | FE_HAS_CARRIER | FE_HAS_VITERBI |
		       FE_HAS_SYNC    | FE_HAS_LOCK;

	if (is_rf_locked)
		return FE_HAS_SIGNAL | FE_HAS_CARRIER;

	return 0;
}