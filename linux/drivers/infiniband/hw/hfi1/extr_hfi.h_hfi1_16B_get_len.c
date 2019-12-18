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
typedef  int /*<<< orphan*/  u16 ;
struct hfi1_16b_header {int* lrh; } ;

/* Variables and functions */
 int OPA_16B_LEN_MASK ; 
 int OPA_16B_LEN_SHIFT ; 

__attribute__((used)) static inline u16 hfi1_16B_get_len(struct hfi1_16b_header *hdr)
{
	return (u16)((hdr->lrh[0] & OPA_16B_LEN_MASK) >> OPA_16B_LEN_SHIFT);
}