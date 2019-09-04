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
typedef  int /*<<< orphan*/  u32 ;
struct whitelist {int dummy; } ;

/* Variables and functions */
 unsigned int RING_MAX_NONPRIV_SLOTS ; 
 int /*<<< orphan*/  get_whitelist_reg (struct whitelist const*,unsigned int) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_results(const struct whitelist *w, const u32 *results)
{
	unsigned int i;

	for (i = 0; i < RING_MAX_NONPRIV_SLOTS; i++) {
		u32 expected = get_whitelist_reg(w, i);
		u32 actual = results[i];

		pr_info("RING_NONPRIV[%d]: expected 0x%08x, found 0x%08x\n",
			i, expected, actual);
	}
}