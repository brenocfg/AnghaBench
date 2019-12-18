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
struct nvkm_sw_chan {int dummy; } ;
struct nv04_sw_chan {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct nv04_sw_chan* nv04_sw_chan (struct nvkm_sw_chan*) ; 

__attribute__((used)) static bool
nv04_sw_chan_mthd(struct nvkm_sw_chan *base, int subc, u32 mthd, u32 data)
{
	struct nv04_sw_chan *chan = nv04_sw_chan(base);

	switch (mthd) {
	case 0x0150:
		atomic_set(&chan->ref, data);
		return true;
	default:
		break;
	}

	return false;
}