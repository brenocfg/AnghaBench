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
typedef  size_t u16 ;
struct tid_group {int dummy; } ;
struct hfi1_ctxtdata {struct tid_group* groups; } ;

/* Variables and functions */

__attribute__((used)) static inline struct tid_group *
hfi1_idx_to_tid_group(struct hfi1_ctxtdata *rcd, u16 idx)
{
	return &rcd->groups[idx];
}