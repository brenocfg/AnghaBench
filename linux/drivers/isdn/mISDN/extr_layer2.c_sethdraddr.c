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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_2__ {int /*<<< orphan*/  A; int /*<<< orphan*/  B; } ;
struct layer2 {int sapi; int tei; TYPE_1__ addr; int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_LAPD ; 
 int /*<<< orphan*/  FLG_LAPD_NET ; 
 int /*<<< orphan*/  FLG_ORIG ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sethdraddr(struct layer2 *l2, u_char *header, int rsp)
{
	u_char *ptr = header;
	int crbit = rsp;

	if (test_bit(FLG_LAPD, &l2->flag)) {
		if (test_bit(FLG_LAPD_NET, &l2->flag))
			crbit = !crbit;
		*ptr++ = (l2->sapi << 2) | (crbit ? 2 : 0);
		*ptr++ = (l2->tei << 1) | 1;
		return 2;
	} else {
		if (test_bit(FLG_ORIG, &l2->flag))
			crbit = !crbit;
		if (crbit)
			*ptr++ = l2->addr.B;
		else
			*ptr++ = l2->addr.A;
		return 1;
	}
}