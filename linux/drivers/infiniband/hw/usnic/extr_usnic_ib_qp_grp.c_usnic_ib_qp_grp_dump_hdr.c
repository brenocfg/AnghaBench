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
 int scnprintf (char*,int,char*) ; 

int usnic_ib_qp_grp_dump_hdr(char *buf, int buf_sz)
{
	return scnprintf(buf, buf_sz, "|QPN\t|State\t|PID\t|VF Idx\t|Fil ID");
}