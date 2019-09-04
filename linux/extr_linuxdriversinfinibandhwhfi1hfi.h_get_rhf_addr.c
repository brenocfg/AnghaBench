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
struct hfi1_ctxtdata {int head; int rhf_offset; scalar_t__ rcvhdrq; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */

__attribute__((used)) static inline __le32 *get_rhf_addr(struct hfi1_ctxtdata *rcd)
{
	return (__le32 *)rcd->rcvhdrq + rcd->head + rcd->rhf_offset;
}