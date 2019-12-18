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
typedef  int u16 ;
struct ast_private {int dummy; } ;

/* Variables and functions */
 int CBR_SIZE0 ; 
 int ast_mindwm (struct ast_private*,int) ; 
 int /*<<< orphan*/  ast_moutdwm (struct ast_private*,int,int) ; 
 scalar_t__ cbr_scan3 (struct ast_private*) ; 

__attribute__((used)) static void finetuneDQSI(struct ast_private *ast)
{
	u32 dlli, dqsip, dqidly;
	u32 reg_mcr18, reg_mcr0c, passcnt[2], diff;
	u32 g_dqidly, g_dqsip, g_margin, g_side;
	u16 pass[32][2][2];
	char tag[2][76];

	/* Disable DQI CBR */
	reg_mcr0c  = ast_mindwm(ast, 0x1E6E000C);
	reg_mcr18  = ast_mindwm(ast, 0x1E6E0018);
	reg_mcr18 &= 0x0000ffff;
	ast_moutdwm(ast, 0x1E6E0018, reg_mcr18);

	for (dlli = 0; dlli < 76; dlli++) {
		tag[0][dlli] = 0x0;
		tag[1][dlli] = 0x0;
	}
	for (dqidly = 0; dqidly < 32; dqidly++) {
		pass[dqidly][0][0] = 0xff;
		pass[dqidly][0][1] = 0x0;
		pass[dqidly][1][0] = 0xff;
		pass[dqidly][1][1] = 0x0;
	}
	for (dqidly = 0; dqidly < 32; dqidly++) {
		passcnt[0] = passcnt[1] = 0;
		for (dqsip = 0; dqsip < 2; dqsip++) {
			ast_moutdwm(ast, 0x1E6E000C, 0);
			ast_moutdwm(ast, 0x1E6E0018, reg_mcr18 | (dqidly << 16) | (dqsip << 23));
			ast_moutdwm(ast, 0x1E6E000C, reg_mcr0c);
			for (dlli = 0; dlli < 76; dlli++) {
				ast_moutdwm(ast, 0x1E6E0068, 0x00001300 | (dlli << 16) | (dlli << 24));
				ast_moutdwm(ast, 0x1E6E0070, 0);
				ast_moutdwm(ast, 0x1E6E0074, CBR_SIZE0);
				if (cbr_scan3(ast)) {
					if (dlli == 0)
						break;
					passcnt[dqsip]++;
					tag[dqsip][dlli] = 'P';
					if (dlli < pass[dqidly][dqsip][0])
						pass[dqidly][dqsip][0] = (u16) dlli;
					if (dlli > pass[dqidly][dqsip][1])
						pass[dqidly][dqsip][1] = (u16) dlli;
				} else if (passcnt[dqsip] >= 5)
					break;
				else {
					pass[dqidly][dqsip][0] = 0xff;
					pass[dqidly][dqsip][1] = 0x0;
				}
			}
		}
		if (passcnt[0] == 0 && passcnt[1] == 0)
			dqidly++;
	}
	/* Search margin */
	g_dqidly = g_dqsip = g_margin = g_side = 0;

	for (dqidly = 0; dqidly < 32; dqidly++) {
		for (dqsip = 0; dqsip < 2; dqsip++) {
			if (pass[dqidly][dqsip][0] > pass[dqidly][dqsip][1])
				continue;
			diff = pass[dqidly][dqsip][1] - pass[dqidly][dqsip][0];
			if ((diff+2) < g_margin)
				continue;
			passcnt[0] = passcnt[1] = 0;
			for (dlli = pass[dqidly][dqsip][0]; dlli > 0  && tag[dqsip][dlli] != 0; dlli--, passcnt[0]++);
			for (dlli = pass[dqidly][dqsip][1]; dlli < 76 && tag[dqsip][dlli] != 0; dlli++, passcnt[1]++);
			if (passcnt[0] > passcnt[1])
				passcnt[0] = passcnt[1];
			passcnt[1] = 0;
			if (passcnt[0] > g_side)
				passcnt[1] = passcnt[0] - g_side;
			if (diff > (g_margin+1) && (passcnt[1] > 0 || passcnt[0] > 8)) {
				g_margin = diff;
				g_dqidly = dqidly;
				g_dqsip  = dqsip;
				g_side   = passcnt[0];
			} else if (passcnt[1] > 1 && g_side < 8) {
				if (diff > g_margin)
					g_margin = diff;
				g_dqidly = dqidly;
				g_dqsip  = dqsip;
				g_side   = passcnt[0];
			}
		}
	}
	reg_mcr18 = reg_mcr18 | (g_dqidly << 16) | (g_dqsip << 23);
	ast_moutdwm(ast, 0x1E6E0018, reg_mcr18);

}