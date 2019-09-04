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
typedef  int u64 ;
struct vmballoon_batch_page {int* pages; } ;

/* Variables and functions */
 int VMW_BALLOON_BATCH_PAGE_MASK ; 

__attribute__((used)) static u64 vmballoon_batch_get_pa(struct vmballoon_batch_page *batch, int idx)
{
	return batch->pages[idx] & VMW_BALLOON_BATCH_PAGE_MASK;
}