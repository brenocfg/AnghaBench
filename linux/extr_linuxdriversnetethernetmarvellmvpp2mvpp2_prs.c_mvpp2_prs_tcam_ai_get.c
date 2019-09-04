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
struct mvpp2_prs_entry {int* tcam; } ;

/* Variables and functions */
 int MVPP2_PRS_AI_MASK ; 
 size_t MVPP2_PRS_TCAM_AI_WORD ; 

__attribute__((used)) static int mvpp2_prs_tcam_ai_get(struct mvpp2_prs_entry *pe)
{
	return pe->tcam[MVPP2_PRS_TCAM_AI_WORD] & MVPP2_PRS_AI_MASK;
}