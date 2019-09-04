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
typedef  int /*<<< orphan*/  u16 ;
struct s5k5baf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  s5k5baf_write_arr_seq (struct s5k5baf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void s5k5baf_write_nseq(struct s5k5baf *state, const u16 *nseq)
{
	int count;

	while ((count = *nseq++)) {
		u16 addr = *nseq++;
		--count;

		s5k5baf_write_arr_seq(state, addr, count, nseq);
		nseq += count;
	}
}