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
typedef  int /*<<< orphan*/  u8 ;
struct dm_verity_fec_io {int /*<<< orphan*/ ** bufs; } ;
struct dm_verity {TYPE_1__* fec; } ;
struct TYPE_2__ {unsigned int rsn; } ;

/* Variables and functions */

__attribute__((used)) static inline u8 *fec_buffer_rs_block(struct dm_verity *v,
				      struct dm_verity_fec_io *fio,
				      unsigned i, unsigned j)
{
	return &fio->bufs[i][j * v->fec->rsn];
}