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
struct page {int dummy; } ;
struct kvmppc_spapr_tce_table {int dummy; } ;

/* Variables and functions */
 unsigned long ALIGN (unsigned long,unsigned long) ; 
 unsigned long PAGE_SIZE ; 

__attribute__((used)) static unsigned long kvmppc_stt_pages(unsigned long tce_pages)
{
	unsigned long stt_bytes = sizeof(struct kvmppc_spapr_tce_table) +
			(tce_pages * sizeof(struct page *));

	return tce_pages + ALIGN(stt_bytes, PAGE_SIZE) / PAGE_SIZE;
}