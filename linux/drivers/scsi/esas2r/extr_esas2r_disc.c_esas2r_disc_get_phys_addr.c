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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct esas2r_sg_context {scalar_t__ length; struct esas2r_adapter* adapter; } ;
struct esas2r_adapter {int /*<<< orphan*/ * uncached; scalar_t__ disc_buffer; scalar_t__ uncached_phys; } ;

/* Variables and functions */
 scalar_t__ ESAS2R_DISC_BUF_LEN ; 
 int /*<<< orphan*/  esas2r_bugon () ; 

__attribute__((used)) static u32 esas2r_disc_get_phys_addr(struct esas2r_sg_context *sgc, u64 *addr)
{
	struct esas2r_adapter *a = sgc->adapter;

	if (sgc->length > ESAS2R_DISC_BUF_LEN)
		esas2r_bugon();

	*addr = a->uncached_phys
		+ (u64)((u8 *)a->disc_buffer - a->uncached);

	return sgc->length;
}