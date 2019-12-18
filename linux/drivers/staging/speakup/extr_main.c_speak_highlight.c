#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vc_data {int vc_num; int vc_y; } ;
struct TYPE_3__ {int cy; scalar_t__* ry; int /*<<< orphan*/ * rx; int /*<<< orphan*/ * rpos; int /*<<< orphan*/ * highsize; int /*<<< orphan*/ * highbuf; } ;
struct TYPE_4__ {TYPE_1__ ht; } ;

/* Variables and functions */
 int count_highlight_color (struct vc_data*) ; 
 int get_highlight_color (struct vc_data*) ; 
 TYPE_2__** speakup_console ; 
 int /*<<< orphan*/  spk_cp ; 
 int /*<<< orphan*/  spk_cx ; 
 scalar_t__ spk_cy ; 
 int /*<<< orphan*/  spk_do_flush () ; 
 int spk_parked ; 
 int /*<<< orphan*/  spk_pos ; 
 int /*<<< orphan*/  spk_x ; 
 scalar_t__ spk_y ; 
 int /*<<< orphan*/  spkup_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int speak_highlight(struct vc_data *vc)
{
	int hc, d;
	int vc_num = vc->vc_num;

	if (count_highlight_color(vc) == 1)
		return 0;
	hc = get_highlight_color(vc);
	if (hc != -1) {
		d = vc->vc_y - speakup_console[vc_num]->ht.cy;
		if ((d == 1) || (d == -1))
			if (speakup_console[vc_num]->ht.ry[hc] != vc->vc_y)
				return 0;
		spk_parked |= 0x01;
		spk_do_flush();
		spkup_write(speakup_console[vc_num]->ht.highbuf[hc],
			    speakup_console[vc_num]->ht.highsize[hc]);
		spk_pos = spk_cp = speakup_console[vc_num]->ht.rpos[hc];
		spk_x = spk_cx = speakup_console[vc_num]->ht.rx[hc];
		spk_y = spk_cy = speakup_console[vc_num]->ht.ry[hc];
		return 1;
	}
	return 0;
}