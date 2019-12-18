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
struct vc_data {int dummy; } ;
struct uni_screen {int /*<<< orphan*/ ** lines; } ;
typedef  enum con_scroll { ____Placeholder_con_scroll } con_scroll ;
typedef  int /*<<< orphan*/  char32_t ;

/* Variables and functions */
 int SM_DOWN ; 
 unsigned int gcd (unsigned int,unsigned int) ; 
 struct uni_screen* get_vc_uniscr (struct vc_data*) ; 
 int /*<<< orphan*/  vc_uniscr_clear_lines (struct vc_data*,unsigned int,unsigned int) ; 

__attribute__((used)) static void vc_uniscr_scroll(struct vc_data *vc, unsigned int t, unsigned int b,
			     enum con_scroll dir, unsigned int nr)
{
	struct uni_screen *uniscr = get_vc_uniscr(vc);

	if (uniscr) {
		unsigned int i, j, k, sz, d, clear;

		sz = b - t;
		clear = b - nr;
		d = nr;
		if (dir == SM_DOWN) {
			clear = t;
			d = sz - nr;
		}
		for (i = 0; i < gcd(d, sz); i++) {
			char32_t *tmp = uniscr->lines[t + i];
			j = i;
			while (1) {
				k = j + d;
				if (k >= sz)
					k -= sz;
				if (k == i)
					break;
				uniscr->lines[t + j] = uniscr->lines[t + k];
				j = k;
			}
			uniscr->lines[t + j] = tmp;
		}
		vc_uniscr_clear_lines(vc, clear, nr);
	}
}