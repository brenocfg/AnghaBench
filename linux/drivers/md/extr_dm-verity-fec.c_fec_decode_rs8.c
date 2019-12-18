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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  u8 ;
struct dm_verity_fec_io {int /*<<< orphan*/  erasures; int /*<<< orphan*/  rs; } ;
struct dm_verity {TYPE_1__* fec; } ;
struct TYPE_2__ {int roots; int /*<<< orphan*/  rsn; } ;

/* Variables and functions */
 int DM_VERITY_FEC_MIN_RSN ; 
 int DM_VERITY_FEC_RSM ; 
 int decode_rs8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fec_decode_rs8(struct dm_verity *v, struct dm_verity_fec_io *fio,
			  u8 *data, u8 *fec, int neras)
{
	int i;
	uint16_t par[DM_VERITY_FEC_RSM - DM_VERITY_FEC_MIN_RSN];

	for (i = 0; i < v->fec->roots; i++)
		par[i] = fec[i];

	return decode_rs8(fio->rs, data, par, v->fec->rsn, NULL, neras,
			  fio->erasures, 0, NULL);
}