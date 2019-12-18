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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  read_csr (struct hfi1_devdata const*,scalar_t__) ; 

__attribute__((used)) static inline u64 read_kctxt_csr(const struct hfi1_devdata *dd, int ctxt,
				 u32 offset0)
{
	/* kernel per-context CSRs are separated by 0x100 */
	return read_csr(dd, offset0 + (0x100 * ctxt));
}