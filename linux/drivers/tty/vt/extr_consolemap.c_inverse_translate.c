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
typedef  int u16 ;
struct vc_data {size_t vc_num; struct uni_pagedir** vc_uni_pagedir_loc; } ;
struct uni_pagedir {int* inverse_trans_unicode; int** inverse_translations; } ;

/* Variables and functions */
 int MAX_GLYPH ; 
 int* inv_translate ; 

u16 inverse_translate(struct vc_data *conp, int glyph, int use_unicode)
{
	struct uni_pagedir *p;
	int m;
	if (glyph < 0 || glyph >= MAX_GLYPH)
		return 0;
	else {
		p = *conp->vc_uni_pagedir_loc;
		if (!p)
			return glyph;
		else if (use_unicode) {
			if (!p->inverse_trans_unicode)
				return glyph;
			else
				return p->inverse_trans_unicode[glyph];
			} else {
			m = inv_translate[conp->vc_num];
			if (!p->inverse_translations[m])
				return glyph;
			else
				return p->inverse_translations[m][glyph];
			}
	}
}