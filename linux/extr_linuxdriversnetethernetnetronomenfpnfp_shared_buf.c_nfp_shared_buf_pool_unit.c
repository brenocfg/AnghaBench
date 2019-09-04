#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nfp_pf {unsigned int num_shared_bufs; TYPE_1__* shared_bufs; } ;
typedef  scalar_t__ __le32 ;
struct TYPE_2__ {scalar_t__ id; int /*<<< orphan*/  pool_size_unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 nfp_shared_buf_pool_unit(struct nfp_pf *pf, unsigned int sb)
{
	__le32 sb_id = cpu_to_le32(sb);
	unsigned int i;

	for (i = 0; i < pf->num_shared_bufs; i++)
		if (pf->shared_bufs[i].id == sb_id)
			return le32_to_cpu(pf->shared_bufs[i].pool_size_unit);

	WARN_ON_ONCE(1);
	return 0;
}