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

/* Variables and functions */
 unsigned int S5P_FIMV_ERR_DEC_MASK ; 
 unsigned int S5P_FIMV_ERR_DEC_SHIFT ; 

__attribute__((used)) static int s5p_mfc_err_dec_v5(unsigned int err)
{
	return (err & S5P_FIMV_ERR_DEC_MASK) >> S5P_FIMV_ERR_DEC_SHIFT;
}