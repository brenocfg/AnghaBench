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
typedef  int u16 ;
struct budget_patch {int dummy; } ;

/* Variables and functions */
 int COMTYPE_AUDIODAC ; 
 int SendDiSEqC ; 
 int /*<<< orphan*/  budget_av7110_send_fw_cmd (struct budget_patch*,int*,int) ; 
 int /*<<< orphan*/  dprintk (int,char*,struct budget_patch*) ; 

__attribute__((used)) static int av7110_send_diseqc_msg(struct budget_patch *budget, int len, u8 *msg, int burst)
{
	int i;
	u16 buf[18] = { ((COMTYPE_AUDIODAC << 8) | SendDiSEqC),
		16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	dprintk(2, "budget: %p\n", budget);

	if (len>10)
		len=10;

	buf[1] = len+2;
	buf[2] = len;

	if (burst != -1)
		buf[3]=burst ? 0x01 : 0x00;
	else
		buf[3]=0xffff;

	for (i=0; i<len; i++)
		buf[i+4]=msg[i];

	budget_av7110_send_fw_cmd(budget, buf, 18);
	return 0;
}