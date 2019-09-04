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
struct ast_private {int dummy; } ;
struct ast2300_dram_param {int dummy; } ;

/* Variables and functions */
 int CBR_SIZE1 ; 
 int CBR_THRESHOLD2 ; 
 int /*<<< orphan*/  ast_moutdwm (struct ast_private*,int,int) ; 
 int cbr_scan2 (struct ast_private*) ; 

__attribute__((used)) static bool finetuneDQI_L(struct ast_private *ast, struct ast2300_dram_param *param)
{
	u32 gold_sadj[2], dllmin[16], dllmax[16], dlli, data, cnt, mask, passcnt, retry = 0;
	bool status = false;
FINETUNE_START:
	for (cnt = 0; cnt < 16; cnt++) {
		dllmin[cnt] = 0xff;
		dllmax[cnt] = 0x0;
	}
	passcnt = 0;
	for (dlli = 0; dlli < 76; dlli++) {
		ast_moutdwm(ast, 0x1E6E0068, 0x00001400 | (dlli << 16) | (dlli << 24));
		ast_moutdwm(ast, 0x1E6E0074, CBR_SIZE1);
		data = cbr_scan2(ast);
		if (data != 0) {
			mask = 0x00010001;
			for (cnt = 0; cnt < 16; cnt++) {
				if (data & mask) {
					if (dllmin[cnt] > dlli) {
						dllmin[cnt] = dlli;
					}
					if (dllmax[cnt] < dlli) {
						dllmax[cnt] = dlli;
					}
				}
				mask <<= 1;
			}
			passcnt++;
		} else if (passcnt >= CBR_THRESHOLD2) {
			break;
		}
	}
	gold_sadj[0] = 0x0;
	passcnt = 0;
	for (cnt = 0; cnt < 16; cnt++) {
		if ((dllmax[cnt] > dllmin[cnt]) && ((dllmax[cnt] - dllmin[cnt]) >= CBR_THRESHOLD2)) {
			gold_sadj[0] += dllmin[cnt];
			passcnt++;
		}
	}
	if (retry++ > 10)
		goto FINETUNE_DONE;
	if (passcnt != 16) {
		goto FINETUNE_START;
	}
	status = true;
FINETUNE_DONE:
	gold_sadj[0] = gold_sadj[0] >> 4;
	gold_sadj[1] = gold_sadj[0];

	data = 0;
	for (cnt = 0; cnt < 8; cnt++) {
		data >>= 3;
		if ((dllmax[cnt] > dllmin[cnt]) && ((dllmax[cnt] - dllmin[cnt]) >= CBR_THRESHOLD2)) {
			dlli = dllmin[cnt];
			if (gold_sadj[0] >= dlli) {
				dlli = ((gold_sadj[0] - dlli) * 19) >> 5;
				if (dlli > 3) {
					dlli = 3;
				}
			} else {
				dlli = ((dlli - gold_sadj[0]) * 19) >> 5;
				if (dlli > 4) {
					dlli = 4;
				}
				dlli = (8 - dlli) & 0x7;
			}
			data |= dlli << 21;
		}
	}
	ast_moutdwm(ast, 0x1E6E0080, data);

	data = 0;
	for (cnt = 8; cnt < 16; cnt++) {
		data >>= 3;
		if ((dllmax[cnt] > dllmin[cnt]) && ((dllmax[cnt] - dllmin[cnt]) >= CBR_THRESHOLD2)) {
			dlli = dllmin[cnt];
			if (gold_sadj[1] >= dlli) {
				dlli = ((gold_sadj[1] - dlli) * 19) >> 5;
				if (dlli > 3) {
					dlli = 3;
				} else {
					dlli = (dlli - 1) & 0x7;
				}
			} else {
				dlli = ((dlli - gold_sadj[1]) * 19) >> 5;
				dlli += 1;
				if (dlli > 4) {
					dlli = 4;
				}
				dlli = (8 - dlli) & 0x7;
			}
			data |= dlli << 21;
		}
	}
	ast_moutdwm(ast, 0x1E6E0084, data);
	return status;
}