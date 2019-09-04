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
typedef  scalar_t__ u32 ;
struct rvt_sge {int /*<<< orphan*/  vaddr; } ;
struct rvt_sge_state {struct rvt_sge sge; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 scalar_t__ rvt_get_sge_length (struct rvt_sge*,scalar_t__) ; 
 int /*<<< orphan*/  rvt_update_sge (struct rvt_sge_state*,scalar_t__,int) ; 

void qib_copy_sge(struct rvt_sge_state *ss, void *data, u32 length, int release)
{
	struct rvt_sge *sge = &ss->sge;

	while (length) {
		u32 len = rvt_get_sge_length(sge, length);

		WARN_ON_ONCE(len == 0);
		memcpy(sge->vaddr, data, len);
		rvt_update_sge(ss, len, release);
		data += len;
		length -= len;
	}
}