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
typedef  enum diag26c_sc { ____Placeholder_diag26c_sc } diag26c_sc ;

/* Variables and functions */
 int /*<<< orphan*/  DIAG_STAT_X26C ; 
 int __diag26c (void*,void*,int) ; 
 int /*<<< orphan*/  diag_stat_inc (int /*<<< orphan*/ ) ; 

int diag26c(void *req, void *resp, enum diag26c_sc subcode)
{
	diag_stat_inc(DIAG_STAT_X26C);
	return __diag26c(req, resp, subcode);
}