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
typedef  enum hfi_version { ____Placeholder_hfi_version } hfi_version ;

/* Variables and functions */
 int hfi_ver ; 

void pkt_set_version(enum hfi_version version)
{
	hfi_ver = version;
}