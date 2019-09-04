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
typedef  int u32 ;
struct hfi1_ctxtdata {int /*<<< orphan*/ * rhf_offset; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int rhf_hdrq_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhf_to_cpu (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void *hfi1_get_header(struct hfi1_ctxtdata *rcd,
				    __le32 *rhf_addr)
{
	u32 offset = rhf_hdrq_offset(rhf_to_cpu(rhf_addr));

	return (void *)(rhf_addr - rcd->rhf_offset + offset);
}