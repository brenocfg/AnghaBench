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
 int ATH6KL_AID_SHIFT ; 

__attribute__((used)) static inline u8 ath6kl_get_aid(u8 tid_mux)
{
	return tid_mux >> ATH6KL_AID_SHIFT;
}