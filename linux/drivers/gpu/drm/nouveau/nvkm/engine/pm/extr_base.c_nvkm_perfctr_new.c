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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct nvkm_perfsig {int dummy; } ;
struct nvkm_perfdom {int signal; int /*<<< orphan*/  list; } ;
struct nvkm_perfctr {int slot; int /*<<< orphan*/  head; int /*<<< orphan*/ ** source; struct nvkm_perfsig** signal; int /*<<< orphan*/  logic_op; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvkm_perfctr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nvkm_perfctr_new(struct nvkm_perfdom *dom, int slot, u8 domain,
		 struct nvkm_perfsig *signal[4], u64 source[4][8],
		 u16 logic_op, struct nvkm_perfctr **pctr)
{
	struct nvkm_perfctr *ctr;
	int i, j;

	if (!dom)
		return -EINVAL;

	ctr = *pctr = kzalloc(sizeof(*ctr), GFP_KERNEL);
	if (!ctr)
		return -ENOMEM;

	ctr->domain   = domain;
	ctr->logic_op = logic_op;
	ctr->slot     = slot;
	for (i = 0; i < 4; i++) {
		if (signal[i]) {
			ctr->signal[i] = signal[i] - dom->signal;
			for (j = 0; j < 8; j++)
				ctr->source[i][j] = source[i][j];
		}
	}
	list_add_tail(&ctr->head, &dom->list);

	return 0;
}