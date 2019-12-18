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
typedef  int u16 ;

/* Variables and functions */
 int I40IW_IEQ_MPA_FRAMING ; 

__attribute__((used)) static u16 i40iw_ieq_get_fpdu_length(u16 length)
{
	u16 fpdu_len;

	fpdu_len = length + I40IW_IEQ_MPA_FRAMING;
	fpdu_len = (fpdu_len + 3) & 0xfffffffc;
	return fpdu_len;
}