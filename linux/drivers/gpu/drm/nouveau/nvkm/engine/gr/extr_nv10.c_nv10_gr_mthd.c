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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nv10_gr_chan {int dummy; } ;

/* Variables and functions */
 int nv17_gr_mthd_celcius (struct nv10_gr_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
nv10_gr_mthd(struct nv10_gr_chan *chan, u8 class, u32 mthd, u32 data)
{
	bool (*func)(struct nv10_gr_chan *, u32, u32);
	switch (class) {
	case 0x99: func = nv17_gr_mthd_celcius; break;
	default:
		return false;
	}
	return func(chan, mthd, data);
}